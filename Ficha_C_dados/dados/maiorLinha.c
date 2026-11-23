#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define LINEMAX 100
int main(int argc, char **argv) {
    FILE *fp= NULL;
    char line[LINEMAX];
    int maxchar = 0;
    char maxline[LINEMAX];
    int chartot;

    if (argc != 2) {
        printf("Só podes meter um ficheiro como argumento!");
        return EXIT_FAILURE;
    }

    errno = 0;

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Erro a abrir o ficheiro!");
        return EXIT_FAILURE;
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        chartot = strlen(line);
        if (chartot > maxchar) {
            maxchar = chartot;
        }
    }

    printf("A linha com maior caracteres tem %d caracteres \n", maxchar);
    return EXIT_SUCCESS;
}