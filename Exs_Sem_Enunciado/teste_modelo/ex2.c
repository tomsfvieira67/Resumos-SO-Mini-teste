#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void listDir(const char *dirname, long min_bytes)
{
    DIR *dp = opendir(dirname);
    if (dp == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    struct dirent *dent;
    char caminho[1024];
    struct stat st;
    int total_ficheiros = 0;
    long total_bytes = 0;

    while ((dent = readdir(dp)) != NULL) {
        if (strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0) {
            continue;
        }

        snprintf(caminho, sizeof(caminho), "%s/%s", dirname, dent->d_name);

        if (stat(caminho, &st) == 0) {
            if (S_ISREG(st.st_mode) && st.st_size >= min_bytes) {
                printf("%s (%ld bytes)\n", dent->d_name, (long)st.st_size);
                total_ficheiros++;
                total_bytes += st.st_size;
            }
        }
    }

    closedir(dp);
    printf("Total: %d ficheiros (%ld bytes)\n", total_ficheiros, total_bytes);
}

int main(int argc, char *argv[])
{
    int opt;
    long min_bytes = 0;

    while ((opt = getopt(argc, argv, "m:")) != -1) {
        switch (opt) {
            case 'm':
                min_bytes = atol(optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s [-m min_bytes] <diretoria>\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (argc - optind != 1) {
        fprintf(stderr, "Erro: indique exatamente uma diretoria.\n");
        return EXIT_FAILURE;
    }

    listDir(argv[optind], min_bytes);
    return EXIT_SUCCESS;
}