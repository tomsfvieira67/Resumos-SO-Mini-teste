#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int i;
    int numtot;
    int numchar;
    int numaior = 0;
    int indice_maior;
    int count;
    if (argc == 1) {
        printf("Introduz algum argumento! \n");
        return EXIT_FAILURE;
    }

    numtot = 0;
    for (i=1; i < argc; i++) {
        numtot += strlen(argv[i]);
        numchar = strlen(argv[i]);
        if (numchar > numaior) {
            numaior = numchar;
            indice_maior = i;
        }
    }


    count = argc - 1;
    printf("Numero de argumentos: %d \n", count);
    printf("Caracteres: %d \n", numtot);
    printf("Maior: %s(%d) \n", argv[indice_maior], numaior);
    return EXIT_SUCCESS;
}