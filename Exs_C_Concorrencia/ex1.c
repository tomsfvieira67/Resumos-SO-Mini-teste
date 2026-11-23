#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    /* TODO 1: Criar um processo filho com fork() */
    pid = fork();

    if (pid < 0) {
        perror("Erro no fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Código executado pelo FILHO */
        /* TODO 2: Substituir a imagem do processo pelo comando "/bin/ls" com os argumentos "ls", "-l" e NULL */
        execl("/bin/ls", "ls", "-l", NULL);

        /* Se chegar aqui, o execl falhou */
        perror("Erro no execl");
        exit(EXIT_FAILURE);
    }
    else {
        /* Código executado pelo PAI */
        /* TODO 3: Esperar pelo término do filho 'pid' guardando o estado em 'status' */
        waitpid(pid, &status, 0);

        /* TODO 4: Verificar se o filho terminou normalmente (WIFEXITED) e imprimir o seu código de saída (WEXITSTATUS) */
        if (WIFEXITED(status) != 0) {
            printf("Filho terminou com código: %d\n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}