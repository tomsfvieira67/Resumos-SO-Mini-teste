#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int i;
    if (argc != 4) {
        printf("Número inválido de argumentos (tem de ser 3) \n");
        return EXIT_FAILURE;
    }

    for (i=1; i<argc; i++) {
        printf("%s \n", argv[argc - i]);
    }

    return EXIT_SUCCESS;
}