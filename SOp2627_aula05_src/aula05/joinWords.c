#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int i;
    int tamanho = 1;
    char *final;

    for (i = 1; i < argc; i++) {
        tamanho += (int)strlen(argv[i]);
    }

    final = malloc(tamanho);
    if (final == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    final[0] = '\0';
    for (i = 1; i < argc; i++) {
        strcat(final, argv[i]);
    }

    printf("%s", final);
    free(final);
    return EXIT_SUCCESS;
}