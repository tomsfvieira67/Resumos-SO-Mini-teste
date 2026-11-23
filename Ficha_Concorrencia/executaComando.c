#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Introduz um número válido de argumentos! \n");
        return EXIT_FAILURE;
    }
    int stat;
    printf("Pai (antes do fork): PID = %u, PPID = %u\n", getpid(), getppid());
    switch (fork())
    {
      case -1: /* fork falhou */
               perror("Erro no fork\n");
               return EXIT_FAILURE;
      case 0:  /* processo filho */
               if (execv(argv[1], &argv[1]) < 0) { 
                   perror("erro no lancamento da aplicacao");
                   exit (127);
               }
               printf("Porque é que eu não apareço?\n");
               break;
      default: /* processo pai */
               wait(&stat);
               if (WIFEXITED(stat) != 0 && WEXITSTATUS(stat) == 0) {
                   printf("Comando terminou com sucesso (código 0)");
               }
               else {
                   printf("O processo filho terminou de forma anormal.\n");
               }
    }

    return EXIT_SUCCESS;
}
