#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int sum;
    if (argc != 3) {
        printf("Introduz apenas dois argumentos. \n");
        return EXIT_FAILURE;
    }

    int num1 = strtol(argv[1], NULL, 10);
    int num2 = strtol(argv[2], NULL, 10);

    sum = num1 + num2;

    printf("A soma dos valores é %d \n", sum);
    return EXIT_SUCCESS;
}