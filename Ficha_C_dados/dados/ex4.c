#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv) {
    int i;
    int j;
    if (argc == 1) {
        printf("Mete um ou mais argumentos bro \n");
        return EXIT_FAILURE;
    }

    for (i=1; i < argc; i++) {
        for (j=0; argv[i][j] != '\0'; j++) {
            argv[i][j] = (char)toupper((unsigned char)argv[i][j]);
        }

        printf("%s ", argv[i]);
    }
    printf(" \n");

    return EXIT_SUCCESS;


}
