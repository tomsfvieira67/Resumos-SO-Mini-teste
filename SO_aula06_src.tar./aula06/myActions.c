#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man system
 man date
*/

int main(int argc, char *argv[])
{
    char text[1024];
    FILE *ficheiro = fopen("comandos.log", "a"); //Write escreve do zero ("w"), Append acrescenta sem apagar o que tava antes("a")
    if (ficheiro == NULL) {
        printf("Erro ao abrir ficheiro!");
        return EXIT_FAILURE;
    }

    fprintf(ficheiro, "\n");
    
    do
    {
        printf("Command: ");
        scanf("%1023[^\n]%*c", text);
        fprintf(ficheiro, "%s \n", text);

        /* system(const char *command) executes a command specified in command
            by calling /bin/sh -c command, and returns after the command has been
            completed.
        */
        if(strcmp(text, "end")) {
           printf("\n * Command to be executed: %s\n", text);
           printf("---------------------------------\n");
           system(text);
           printf("---------------------------------\n");
        }
    } while(strcmp(text, "end"));

    printf("-----------The End---------------\n");
    fprintf(ficheiro, "Fim da Sessão \n");
    fclose(ficheiro);

    return EXIT_SUCCESS;
}
