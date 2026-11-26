#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define LINEMAXSIZE 80

int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    char line[LINEMAXSIZE];
    int i;

    /* TODO 1: Validar que o utilizador passou PELO MENOS um ficheiro como argumento */
    if (argc < 2) {
        printf("USAGE: %s fileName1 [fileName2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* TODO 2: Criar um ciclo para percorrer TODOS os ficheiros passados em argv */
    for (i=1; i < argc; i++)
    {
        errno = 0;
        /* TODO 3: Abrir o ficheiro atual em modo leitura ("r") */
        fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            perror("Error opening file!");
            continue; /* passa ao próximo ficheiro se este falhar */
        }

        int numLinha = 1;

        /* TODO 4: Ler todas as linhas do ficheiro com fgets e imprimir com o número da linha */
        while (fgets(line, sizeof(line), fp) != NULL)
        {
            printf("%d: %s", numLinha, line);
            numLinha++;
        }

        fclose(fp);
    }

    return EXIT_SUCCESS;
}