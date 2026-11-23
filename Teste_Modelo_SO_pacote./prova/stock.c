/* =====================================================================
 * Questão 2 (C sem concorrência) - stock.c                    [7 valores]
 * Uso: ./stock [-m min] [-s] ficheiro
 *
 * O ficheiro tem uma linha por produto:  nome quantidade preço
 *   (ex.: "martelo 5 12.50"; no máx. 100 produtos; nome sem espaços).
 *
 * -s      ordena a listagem por valor total (qtd*preço), do maior para o menor.
 * -m N    marca com "  REPOR" os produtos com quantidade < N e, no fim, mostra
 *         "Produtos a repor: <n>". N tem de ser um inteiro >= 0.
 *
 * Saída para "./stock stock.txt":
 *   Produto      Qtd    Preco     Valor
 *   parafuso     120     0.05      6.00
 *   ...
 *   Valor total em stock: 244.60
 *
 * Em caso de erro (opção inválida, valor de -m inválido, nº de argumentos
 * errado, ficheiro inexistente) escrever mensagem em stderr e terminar com
 * EXIT_FAILURE. Completa os blocos TODO.
 * ===================================================================== */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 100

typedef struct {
    char   nome[32];
    int    qtd;
    double preco;
} Item;

static void uso(const char *prog) {
    fprintf(stderr, "Uso: %s [-m min] [-s] ficheiro\n", prog);
}

/* TODO 3 (1 val) - comparador para o qsort: ordem DECRESCENTE do valor total (qtd*preco) */
static int cmpValorDesc(const void *a, const void *b) {
    /* ... completa ... */
    return 0;
}

int main(int argc, char *argv[]) {
    int minimo = -1;                /* -1 significa "opção -m não usada" */
    int ordenar = 0;

    /* TODO 1 (2 val) - opções com getopt: -m (com valor, validado com strtol) e -s.
     * Depois das opções tem de sobrar exatamente 1 argumento (o ficheiro). */

    /* TODO 2 (2 val) - abrir o ficheiro (testar erro) e ler os produtos para o array v
     * (usa fscanf; no máximo MAX produtos; devolve em n o nº de produtos lidos). */
    Item v[MAX];
    int n = 0;

    if (ordenar)
        qsort(v, n, sizeof(Item), cmpValorDesc);

    /* TODO 4 (2 val) - imprimir o cabeçalho (printf("%-10s %5s %8s %9s\n", ...)), uma linha por
     * produto (printf("%-10s %5d %8.2f %9.2f", ...)), a marca "  REPOR" quando aplicável,
     * o valor total e, se -m foi usada, o nº de produtos a repor. */

    (void)argc; (void)argv; (void)minimo;
    return EXIT_SUCCESS;
}
