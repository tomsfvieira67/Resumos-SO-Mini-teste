#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LINEMAX 100
int main(int argc, char **argv) {
    FILE *fp= NULL;
    char line[LINEMAX];
    int i;
    int count = 0;
    int chartot = 0;

    if (argc == 1) {
        printf("Mete argumentos depois \n");
        return EXIT_FAILURE;
    }

    errno = 0;

    for (i=1; i<argc; i++) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            perror("Erro a abrir o ficheiro!");
            return EXIT_FAILURE;
        }

        printf("%s: \n", argv[i]);
        while (fgets(line, sizeof(line), fp) != NULL) {
            count += 1;
            chartot += strlen(line);
        }

        printf("Linhas: %d \n", count);
        printf("Caracteres: %d \n", chartot);
        count = 0;
        chartot = 0;
    }

    return EXIT_SUCCESS;
    
}