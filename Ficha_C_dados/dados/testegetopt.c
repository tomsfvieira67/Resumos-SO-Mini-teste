#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int opt;
    int contar_linhas = 0;
    int contar_caracteres = 0;

    while ((opt = getopt(argc, argv, "lc")) != -1) {
        switch (opt) {
            case 'l':
                contar_linhas = 1;
                break;
            case 'c':
                contar_caracteres = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-l] [-c] ficheiro [ficheiro ...]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        return EXIT_FAILURE;
    }

    if (!contar_linhas && !contar_caracteres) {
        contar_linhas = 1;
        contar_caracteres = 1;
    }

    for (int i = optind; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "Erro ao abrir %s: %s\n", argv[i], strerror(errno));
            continue;
        }

        long linhas = 0;
        long caracteres = 0;
        int ch;

        while ((ch = fgetc(fp)) != EOF) {
            caracteres++;
            if (ch == '\n') {
                linhas++;
            }
        }

        if (ferror(fp)) {
            perror(argv[i]);
            fclose(fp);
            continue;
        }
        fclose(fp);

        if (contar_linhas) {
            printf("%ld ", linhas);
        }
        if (contar_caracteres) {
            printf("%ld ", caracteres);
        }
        printf("%s\n", argv[i]);
    }

    return EXIT_SUCCESS;
}