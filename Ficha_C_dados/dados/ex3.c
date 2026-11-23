#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv) {
    double sum = 0;
    int i;
    double num;
    char *endptr;

    if (argc == 1) {
        printf("Introduz um argumento! \n");
        return EXIT_FAILURE;
    }

    for ( i=1; i < argc; i++) {
        num = strtod(argv[i], &endptr);
        sum += num;
    }

    printf("Soma: %lf \n", sum);
    return EXIT_SUCCESS;
}