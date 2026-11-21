#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man fopen
 man fgets
*/

#define LINEMAXSIZE 500 /* or other suitable maximum line size */


int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    char line [LINEMAXSIZE]; 
    int i;

    /* Validate number of arguments */
    if( argc < 2 )
    {
        printf("Introduz um argumento de ficheiro!");
        return EXIT_FAILURE;
    }

    errno = 0;
    int line_count=0;
    
    /* Open the file provided as argument */
    for (i=1; i < argc; i++) {
        fp = fopen(argv[i], "r");
        if( fp == NULL )
        {
            perror ("Error opening file!");
            continue;
        }

        /* Read all the lines of the file */
        while( fgets(line, sizeof(line), fp) != NULL )
        {
            line_count += 1;
            printf("%d -> %s", line_count, line);
            /* not needed to add '\n' to printf because fgets will read the '\n' that ends each line in the file */
        }
        line_count=0;
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
