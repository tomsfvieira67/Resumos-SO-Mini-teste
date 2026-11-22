#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void listDir(char dirname[])
{
    DIR *dp;
    struct dirent *dent;
    struct stat st;
    char path[1024];

    dp = opendir(dirname);
    if (dp == NULL)
    {
        perror("Error opening directory");
        return;
    }

    dent = readdir(dp);
    while (dent != NULL)
    {
        if (dent->d_name[0] != '.') /* ignora ".", ".." e ocultos */
        {
            /* TODO 1: Construir em 'path' o caminho completo ("dirname/d_name") usando snprintf */
            snprintf(path, sizeof(path), "%s/%s",dirname,dent->d_name);;

            /* TODO 2: Obter informações sobre 'path' usando stat() e verificar se falhou (< 0) */
            if (stat(path, &st) < 0)
            {
                dent = readdir(dp);
                continue;
            }

            /* TODO 3: Verificar com S_ISDIR(st.st_mode) se é uma diretoria.
               Se for: imprimir "d %s\n" e chamar listDir() recursivamente.
               Caso contrário: imprimir "  %s\n" */
            if (S_ISDIR(st.st_mode))
            {
                printf("d %s\n", path);
                listDir(path);
            }
            else
            {
                printf("  %s\n", path);
            }
        }

        dent = readdir(dp);
    }

    /* TODO 4: Fechar o descritor da diretoria 'dp' */
    closedir(dp);
}