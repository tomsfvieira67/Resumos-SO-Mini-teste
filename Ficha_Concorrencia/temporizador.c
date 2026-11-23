#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t tempo_esgotado = 0;


int main(int argc, char *argv[])
{
    struct sigaction sa;
    sa.sa_handler = trataAlarme;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGALRM, &sa, NULL) < 0) {
        perror("Erro no sigaction");
        return EXIT_FAILURE;
    }

    alarm(5);

    while (!tempo_esgotado) {
        printf("A aguardar...\n");
        sleep(1);
    }

    printf("Tempo esgotado! A sair...\n");
    return EXIT_SUCCESS;
}

void trataAlarme (int signum)
{
    (void)signum;
    tempo_esgotado = 1;
    
}