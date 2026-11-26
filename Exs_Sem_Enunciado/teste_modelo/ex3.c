#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

long total_chars = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *conta_chars(void *arg) {
    char *nome_ficheiro = (char *)arg;
    FILE *fp = fopen(nome_ficheiro, "r");
    if (fp == NULL) {
        // Se o ficheiro não abrir, a thread termina sem somar
        return NULL;
    }

    long local_chars = 0;
    while (fgetc(fp) != EOF) {
        local_chars++;
    }
    fclose(fp);

    // Secção crítica protegida por mutex
    pthread_mutex_lock(&mutex);
    total_chars += local_chars;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    // 1. Validação dos argumentos (pelo menos 1 ficheiro)
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <ficheiro1> [ficheiro2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int N = argc - 1;
    pthread_t thr[N];

    // 2. Fase 1: Criar N threads (uma por ficheiro)
    for (int i = 0; i < N; i++) {
        if (pthread_create(&thr[i], NULL, conta_chars, argv[i + 1]) != 0) {
            perror("Erro ao criar thread");
            return EXIT_FAILURE;
        }
    }

    // Esperar por todas as threads (NOTA: thr[i] SEM '&')
    for (int i = 0; i < N; i++) {
        pthread_join(thr[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    printf("Total de carateres: %ld\n", total_chars);

    // 3. Fase 2: Processo filho para registar a conclusão
    pid_t pid = fork();
    if (pid < 0) {
        perror("Erro no fork");
        return EXIT_FAILURE;
    } else if (pid == 0) {
        // Processo filho
        execl("/bin/echo", "echo", "Processamento concluido com sucesso!", NULL);
        perror("Erro no execl");
        exit(1);
    } else {
        // Processo pai
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Filho terminou com código %d\n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}