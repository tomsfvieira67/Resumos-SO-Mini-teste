#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PESSOAS 100

typedef struct {
    char nome[50];
    int idade;
    double altura;
} Person;

/* TODO 1: Implementar a função de comparação para o qsort:
   - 1.º critério: idade DECRESCENTE (mais velho primeiro)
   - 2.º critério (empate): nome ALFABÉTICO CRESCENTE (strcmp) */
int cmp_person(const void *a, const void *b) {
    const Person *p1 = (const Person *)a;
    const Person *p2 = (const Person *)b;

    if (p1->idade != p2->idade) {
        return (p2->idade > p1->idade) - (p2->idade < p1->idade);
    }
    return strcmp(p1->nome, p2->nome);
}

int main(int argc, char *argv[]) {
    int opt;
    int limite = MAX_PESSOAS;

    /* TODO 2: Configurar getopt para aceitar a opção '-n' COM argumento */
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                limite = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s [-n limite] <ficheiro>\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    /* TODO 3: Verificar se foi passado exatamente 1 argumento posicional após as opções
       (Dica: argc - optind != 1) */
    if ((argc - optind) != 1) {
        fprintf(stderr, "Erro: indique o ficheiro de entrada.\n");
        return EXIT_FAILURE;
    }

    /* TODO 4: Abrir o ficheiro indicado em argv[optind] em modo de leitura ("r") */
    FILE *fp = fopen(argv[optind], "r");
    if (fp == NULL) {
        perror(argv[optind]);
        return EXIT_FAILURE;
    }

    Person lista[MAX_PESSOAS];
    int count = 0;

    while (count < MAX_PESSOAS &&
           fscanf(fp, "%49s %d %lf", lista[count].nome, &lista[count].idade, &lista[count].altura) == 3) {
        count++;
    }

    /* TODO 5: Fechar o ficheiro */
    fclose(fp);

    /* TODO 6: Ordenar 'lista' (com 'count' elementos) usando qsort e cmp_person */
    qsort(lista, count, sizeof(Person), cmp_person);;

    int mostrar = (limite < count) ? limite : count;
    for (int i = 0; i < mostrar; i++) {
        printf("%s - %d anos (%.2fm)\n", lista[i].nome, lista[i].idade, lista[i].altura);
    }

    return EXIT_SUCCESS;
}