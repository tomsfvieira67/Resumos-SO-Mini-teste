#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4
#define INCREMENTOS 100000

int contador = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *tarefa(void *arg) {
    for (int i = 0; i < INCREMENTOS; i++) {
        /* TODO 1: Fechar o cadeado (mutex) antes de alterar a variável global 'contador' */
        pthread_mutex_lock (&mutex);

        contador++;

        /* TODO 2: Abrir o cadeado (mutex) depois de alterar 'contador' */
        pthread_mutex_unlock (&mutex);
    }
    return NULL;
}

int main(void) {
    pthread_t tids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        /* TODO 3: Criar a thread i usando pthread_create(&tids[i], NULL, tarefa, NULL) */
        if (pthread_create (&tids[i], NULL, tarefa, NULL) != 0) {
            perror("Erro ao criar thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        /* TODO 4: Esperar pelo término da thread i usando pthread_join() */
        pthread_join(tids[i], NULL);
    }

    printf("Valor esperado: %d | Valor obtido: %d\n", NUM_THREADS * INCREMENTOS, contador);
    pthread_mutex_destroy(&mutex);

    return EXIT_SUCCESS;
}