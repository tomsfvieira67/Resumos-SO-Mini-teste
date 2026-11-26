#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

/* Lista as entradas visiveis encontradas dentro da diretoria indicada. */
void listDir(char dirname[])
{
    DIR *dp; 
    struct dirent *dent;

    dp = opendir(dirname); 
    if(dp == NULL)
    {
        perror("Error opening directory");
        return;
    }

    dent = readdir(dp);
    while(dent!=NULL) 
    {
        if(dent->d_name[0] != '.') /* do not list hidden dirs/files */
        {
          printf("d %s/  %s\n",dirname,dent->d_name);
        }

        dent = readdir(dp);
    }

    closedir(dp);
}

/* Lista ficheiros regulares e, se indicada, limita a extensao pedida. */
void listFich(char dirname[], char *extension)
{
    DIR *dp; 
    struct dirent *dent;

    dp = opendir(dirname); 
    if(dp == NULL)
    {
        perror("Error opening directory");
        return;
    }

    dent = readdir(dp);
    while(dent!=NULL) 
    {
        char *dot = strrchr(dent->d_name, '.');
        int extensionMatches = extension == NULL ||
            (dot != NULL && strcmp(dot + 1, extension) == 0);

        if(dent->d_name[0] != '.' && dent->d_type == DT_REG &&
           extensionMatches)
        {
          printf("%s\n", dent->d_name);
        }

        dent = readdir(dp);
    }

    closedir(dp);
}

int main(int argc, char *argv[]) {
    int opt;
    int onlyFiles = 0;
    int onlyDirs = 0;
    char *extension = NULL;

    /* Le as opcoes: -f e -d nao recebem argumento; -e recebe a extensao. */
    while ((opt = getopt(argc, argv, "fde:")) != -1)
    {
        switch (opt)
        {
            case 'f':
                onlyFiles = 1;
                break;
            case 'd':
                onlyDirs = 1;
                break;
            case 'e':
                extension = optarg;
                break;
                /* If getopt() finds an option character in argv that was not included in
                  optstring, or if it detects a missing option argument, it returns '?'
                 */
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-f] [-d] [-e ext] [directory ...]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    /* Se nao foram indicadas diretorias, usa a diretoria atual. */
    if (optind == argc) {
        if (onlyDirs) {
            listDir(".");
        }
        else {
            listFich(".", extension);
        }
    }

    /* Caso contrario, aplica as opcoes a cada diretoria restante. */
    else {
        for (int i = optind; i < argc; i++) {
            if (onlyDirs) {
                listDir(argv[i]);
            }
            else {
                listFich(argv[i], extension);
            }
            
        }
    }

    return EXIT_SUCCESS;
}