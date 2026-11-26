#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <limits.h>

static int parse_int(const char *text, int *value) {
    char *end;
    long parsed;

    errno = 0;
    parsed = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int) parsed;
    return 1;
}

int main(int argc, char *argv[]) {
    int min;
    int max;

    if (argc != 3 || !parse_int(argv[1], &min) || !parse_int(argv[2], &max) || min >= max) {
        fprintf(stderr, "Utilização: %s <mínimo> <máximo> (mínimo < máximo)\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((long long) max - min + 1 > (long long) RAND_MAX + 1) {
        fprintf(stderr, "O intervalo é demasiado grande.\n");
        return EXIT_FAILURE;
    }

    srand(time(NULL));

    int guess = 0;
    int tries = 0;

    int answer = (int) ((long long) rand() % ((long long) max - min + 1) + min);

    while (guess != answer) {
        printf("Introduz um número de %d a %d: ", min, max);
        scanf("%d" , &guess);
        tries++;
        if (guess < answer) {
            printf("Maior!\n");
            continue;
        }
        else if (guess > answer) {
            printf("Menor!\n");
            continue;
        }
        else {
            printf("Parabéns!\n");
            break;
        }
    }

    printf("Acertaste em %d tentativas!\n", tries);

    return 0;
}
