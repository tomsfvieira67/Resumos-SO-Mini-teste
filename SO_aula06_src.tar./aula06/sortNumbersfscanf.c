#include <stdio.h>
#include <stdlib.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man qsort
*/

int compareInts(const void *px1, const void *px2)
{
    int x1 = *((int *)px1);
    int x2 = *((int *)px2);
    /* qsort usa este resultado para ordenar os inteiros por ordem crescente. */
    return(x1 < x2 ? -1 : x1 == x2 ? 0 : 1);
}

int main(int argc, char *argv[])
{
    int i;
    int numSize = 0;
    int *numbers = NULL;
    int capacity = 0;
    FILE *fp = NULL;

    /* O unico argumento esperado e o nome do ficheiro a ler. */
    if (argc != 2) {
        printf("Introduz um argumento depois do ficheiro! \n");
        return EXIT_FAILURE;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror ("Error opening file");
        return EXIT_FAILURE;
    }

    int value;

    /*
     * fscanf tenta ler um inteiro por iteracao e ignora espacos e mudancas
     * de linha; assim, os numeros podem estar na mesma linha ou em linhas diferentes.
     */
    while (fscanf(fp, "%d", &value) == 1) {
        /* Aumenta o array quando ja nao ha espaco para guardar outro numero. */
        if (numSize == capacity) {
            int newCapacity = (capacity == 0) ? 4 : capacity * 2;
            int *temp = realloc(numbers, newCapacity * sizeof(int));

            if (temp == NULL) {
                perror("realloc");
                free(numbers);
                fclose(fp);
                return EXIT_FAILURE;
            }
            numbers = temp;
            capacity = newCapacity;
        }

        /* Guarda o numero lido no fim do array e atualiza a quantidade. */
        numbers[numSize] = value;
        numSize++;
    }

    /* Ordena todos os numeros lidos antes de os imprimir. */
    qsort(numbers, numSize, sizeof(int), compareInts);

    /* Imprime os numeros ja ordenados. */
    printf("Sorted numbers: \n");
    for(i = 0 ; i < numSize ; i++)
    {
        printf("%d\n", numbers[i]);
    }

    /* Fecha o ficheiro e liberta a memoria reservada para o array. */
    fclose(fp);
    free(numbers);

    return EXIT_SUCCESS;
}