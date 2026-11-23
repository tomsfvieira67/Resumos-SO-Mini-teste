#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct {
    int age;
    double height;
    char name[64];
} Person;

/* Função que abre um ficheiro binário e imprime pessoas com age >= minAge */
void filtraFicheiroBinario(const char *filepath, int minAge) {
    Person p;
    /* TODO 1: Abrir 'filepath' em modo de leitura binária ("rb") */
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) {
        perror(filepath);
        return;
    }

    /* TODO 2: Ler todos os registos 'Person' do ficheiro usando fread() em ciclo */
    while ((fread(&p, sizeof(Person), 1, fp)) == 1) {
        if (p.age >= minAge) {
            printf("[%s] %s (%d anos, %.2fm)\n", filepath, p.name, p.age, p.height);
        }
    }

    fclose(fp);
}

/* Função recursiva adaptada de dirList.c */
void pesquisaDir(const char *dirname, int recursivo, int minAge) {
    DIR *dp = opendir(dirname);
    struct dirent *dent;
    struct stat st;
    char path[1024];

    if (dp == NULL) {
        perror(dirname);
        return;
    }

    while ((dent = readdir(dp)) != NULL) {
        if (dent->d_name[0] != '.') {
            snprintf(path, sizeof(path), "%s/%s", dirname, dent->d_name);

            if (stat(path, &st) < 0) {
                continue;
            }

            /* TODO 3: Se for diretoria (S_ISDIR) E 'recursivo' estiver ativo,
               chamar pesquisaDir() recursivamente;
               senão, se for ficheiro regular (S_ISREG), chamar filtraFicheiroBinario() */
            if (S_ISDIR(st.st_mode) && recursivo) {
                pesquisaDir(path, recursivo, minAge);
            }
            else if (S_ISDIR(st.st_mode)) {
                filtraFicheiroBinario(path, minAge);
            }
        }
    }

    /* TODO 4: Fechar a diretoria 'dp' */
    closedir(dp);
}

int main(int argc, char *argv[]) {
    int opt;
    int recursivo = 0;
    int minAge = 0;

    /* TODO 5: Configurar getopt para aceitar '-r' (sem arg) e '-a' (com arg) */
    while ((opt = getopt(argc, argv, "ra:")) != -1) {
        switch (opt) {
            case 'r':
                recursivo = 1;
                break;
            case 'a':
                minAge = (int)strtol(optarg, NULL, 10);
                break;
            default:
                fprintf(stderr, "Usage: %s [-r] [-a minAge] dir1 [dir2 ...]\n", argv[0]);
                return EXIT_FAILURE;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Erro: indique pelo menos uma diretoria.\n");
        return EXIT_FAILURE;
    }

    /* TODO 6: Percorrer todas as diretorias passadas a partir de 'optind' até 'argc' */
    for (int i = optind; i < argc; i++) {
        pesquisaDir(argv[i], recursivo, minAge);
    }

    return EXIT_SUCCESS;
}