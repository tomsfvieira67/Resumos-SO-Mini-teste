#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
  man opendir
  man readdir
*/

void listDir(char dirname[])
{
    DIR *dp; 
    struct dirent *dent;
    int count = 0;

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
          printf("%s/%s\n",dirname,dent->d_name);
          count += 1;
        }

        dent = readdir(dp);
    }

    printf("Ficheiros: %d \n", count);

}

int main(int argc, char *argv[])
{
    int countdir;
    
    if(argc != 2)
    {
        fprintf(stderr,"Usage: %s base_directory\n",argv[0]);
        return EXIT_FAILURE;
    }

    countdir = argc -1;

    listDir(argv[1]);
    printf("Diretorias: %d \n", countdir);
    
    return EXIT_SUCCESS;
}