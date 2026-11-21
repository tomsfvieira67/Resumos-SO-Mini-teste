#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAXPESSOAS 100

typedef struct
{
    int age;
    double height;
    char name[64];
} Person;

void printPersonInfo(Person *p)
{
    printf("Person: %s, %d, %f\n", p->name, p->age, p->height);
}

int main (int argc, char *argv[])
{
    FILE *fp = NULL;
    Person p[MAXPESSOAS];
    int count = 0;
    int quantidade;
    int i;

    /* Validate number of arguments */
    if(argc != 2)
    {
        printf("USAGE: %s fileName\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open the file provided as argument */
    errno = 0;
    fp = fopen(argv[1], "rb");
    if(fp == NULL)
    {
        perror ("Error opening file!");
        return EXIT_FAILURE;
    }

    /* Carrega no array os registos de pessoas que ja existem no ficheiro. */
    while (count < MAXPESSOAS && fread(&p[count], sizeof p[count], 1, fp) == 1) {
        count++;
    }

    fclose(fp);
    fp = NULL;

    /* Pede quantas pessoas novas serao acrescentadas ao array. */
    printf("Quantas pessoas novas queres adicionar: ");
    if (scanf("%d", &quantidade) != 1 ||
        quantidade < 0 || quantidade > MAXPESSOAS - count) {
        fprintf(stderr, "Quantidade invalida ou sem espaco no array.\n");
        return EXIT_FAILURE;
    }

    if (quantidade == 0) {
        return EXIT_SUCCESS;
    }

    /* Reutiliza a leitura existente, guardando cada pessoa na proxima posicao livre. */
    for (i = 0; i < quantidade; i++) {
        int pos = count + i;

        printf("Introduza a idade da pessoa %d: ", pos + 1);
        scanf("%d", &p[pos].age);

        printf("Introduza a altura da pessoa %d: ", pos + 1);
        scanf("%lf", &p[pos].height);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Introduza o nome da pessoa %d: ", pos + 1);
        fgets(p[pos].name, sizeof(p[pos].name), stdin);
        p[pos].name[strcspn(p[pos].name, "\n")] = '\0';
    }

    /* Reabre em modo de escrita binaria para gravar o array completo. */
    fp = fopen(argv[1], "wb");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    /* Escreve as pessoas antigas e as novas, agora reunidas no array. */
    if (fwrite(p, sizeof p[0], (size_t)(count + quantidade), fp) !=
        (size_t)(count + quantidade)) {
        perror("Error writing file");
        fclose(fp);
        return EXIT_FAILURE;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
