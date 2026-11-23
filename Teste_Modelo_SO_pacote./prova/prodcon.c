/* =====================================================================
 * Questão 3 (C com concorrência) - prodcon.c                  [7 valores]
 *
 * N_PROD produtores colocam, cada um, ITEMS_PER_PROD valores numa FIFO limitada
 * (FIFO_SIZE posições), usando fifoPut. O produtor de id p produz os valores
 * p*100+1, p*100+2, ..., p*100+ITEMS_PER_PROD.
 * N_CONS consumidores retiram, cada um, ITEMS_PER_CONS valores com fifoGet,
 * somam-nos (campo soma) e atualizam as estatísticas globais (totalGlobal e
 * consumidos), que são partilhadas.
 *
 * Saída esperada (a soma de cada consumidor varia; o Total não):
 *   Consumidor 1: soma = ...
 *   Consumidor 2: soma = ...
 *   Total: 3110 (20 itens)
 *   Verificacao: OK
 *
 * Compilar: gcc -Wall -o prodcon prodcon.c -pthread
 * Completa os blocos TODO.
 *
 * TODO 5 (1 val) - responde aqui, em 2 ou 3 linhas cada:
 * (a) Porque é que as esperas em fifoPut/fifoGet usam while e não if?
 *     RESPOSTA:
 * (b) O que poderia acontecer se os consumidores atualizassem totalGlobal sem
 *     usar statsLock?
 *     RESPOSTA:
 * ===================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define FIFO_SIZE      4
#define N_PROD         2
#define N_CONS         2
#define ITEMS_PER_PROD 10
#define ITEMS_PER_CONS 10

/* ================= monitor FIFO ================= */
static int buf[FIFO_SIZE];
static int in = 0, out = 0, count = 0;
static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t notFull  = PTHREAD_COND_INITIALIZER;
static pthread_cond_t notEmpty = PTHREAD_COND_INITIALIZER;

/* TODO 1 (1.5 val) - insere v na FIFO. Se estiver cheia, espera. Depois de inserir,
 * avisa quem possa estar à espera de itens. */
void fifoPut(int v) {
    (void)v;
    /* ... completa ... */
}

/* TODO 2 (1.5 val) - retira e devolve o valor mais antigo. Se estiver vazia, espera.
 * Depois de retirar, avisa quem possa estar à espera de espaço. */
int fifoGet(void) {
    /* ... completa ... */
    return 0;
}

/* ================= estatísticas partilhadas ================= */
static long totalGlobal = 0;       /* soma de todos os valores consumidos */
static int  consumidos  = 0;       /* nº total de itens consumidos */
static pthread_mutex_t statsLock = PTHREAD_MUTEX_INITIALIZER;

typedef struct { int id; long soma; } Arg;

void *produtor(void *p) {
    Arg *a = p;
    for (int k = 1; k <= ITEMS_PER_PROD; k++)
        fifoPut(a->id * 100 + k);
    return NULL;
}

void *consumidor(void *p) {
    Arg *a = p;
    a->soma = 0;
    for (int k = 0; k < ITEMS_PER_CONS; k++) {
        int v = fifoGet();
        a->soma += v;
        /* TODO 3 (1 val) - atualizar totalGlobal (+= v) e consumidos (++) de forma
         * segura, usando statsLock. */
    }
    return NULL;
}

int main(void) {
    pthread_t tp[N_PROD], tc[N_CONS];
    static Arg ap[N_PROD], ac[N_CONS];

    /* TODO 4 (2 val) - criar os N_PROD produtores (ids 1..N_PROD) e os N_CONS consumidores
     * (ids 1..N_CONS), passando a cada um o seu Arg; testar erros de pthread_create;
     * no fim esperar por TODAS as threads. */
    (void)tp; (void)tc; (void)ap;

    for (int i = 0; i < N_CONS; i++)
        printf("Consumidor %d: soma = %ld\n", ac[i].id, ac[i].soma);
    printf("Total: %ld (%d itens)\n", totalGlobal, consumidos);

    long esperado = 0;
    for (int p = 1; p <= N_PROD; p++)
        esperado += (long)p * 100 * ITEMS_PER_PROD + ITEMS_PER_PROD * (ITEMS_PER_PROD + 1) / 2;
    printf("Verificacao: %s\n", totalGlobal == esperado ? "OK" : "ERRO");
    return EXIT_SUCCESS;
}
