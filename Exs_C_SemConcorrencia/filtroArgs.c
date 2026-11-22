#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv) {
    size_t minLen = 3;
    char *env_val = getenv("MINLEN");
    int i;
    int j;

    if (env_val != NULL && env_val[0] != '\0') {
        char *endptr;
        long val = strtol(env_val, &endptr, 10);
        if (*endptr == '\0' && val > 0) {
        minLen = (int)val;
        }
    }
    else {
        minLen = 3;
    }

    for (i=1; i < argc; i++) {
        if (!isalpha((unsigned char)argv[i][0])) {
            continue;
        }
        else {
            if (strlen(argv[i]) < minLen) {
                continue;
            }
            else {
                for (j = 0; argv[i][j] != '\0'; j++) {
                    argv[i][j] = toupper((unsigned char)argv[i][j]);
                }
            printf("%s \n", argv[i]);

            }
        }

    }
    return EXIT_SUCCESS;
}