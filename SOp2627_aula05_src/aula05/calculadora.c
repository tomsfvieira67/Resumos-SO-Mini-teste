#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Introduza o número de argumentos adequados! \n");
        return EXIT_FAILURE;
    }

    char *end;
    double num1 = strtod(argv[1], &end);
    if (*argv[1] == '\0' || *end != '\0') {
        printf("Introduza números válidos!\n");
        return EXIT_FAILURE;
    }

    double num2 = strtod(argv[3], &end);
    if (*argv[3] == '\0' || *end != '\0') {
        printf("Introduza números válidos!\n");
        return EXIT_FAILURE;
    }

    double result;
    if (argv[2][0] == '+' && argv[2][1] == '\0') {
        result = num1 + num2;
    }
    else if (argv[2][0] == '-' && argv[2][1] == '\0') {
        result = num1 - num2;
    }
    else if (argv[2][0] == 'x' && argv[2][1] == '\0') {
        result = num1 * num2;
    }
    else if (argv[2][0] == '/' && argv[2][1] == '\0') {
        if (num2 == 0.0) {
            printf("Não é possível dividir por zero!\n");
            return EXIT_FAILURE;
        }
        result = num1 / num2;
    }
    else if (argv[2][0] == 'p' && argv[2][1] == '\0') {
        result = pow(num1, num2);
    }
    else {
        printf("Introduza uma opção válida!\n");
        return EXIT_FAILURE;
    }

    printf("O resultado é %lf \n", result);
    return EXIT_SUCCESS;
}