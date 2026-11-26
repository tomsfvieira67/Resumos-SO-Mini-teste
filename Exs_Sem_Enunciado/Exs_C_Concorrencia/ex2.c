#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t parar = 0;

/* TODO 1: Definir a função handler 'trataSinal' que recebe 'int signum'
   e coloca a flag 'parar = 1' */
void trataSinal(int signum) {
    parar = 1;
}

int main(void) {
    struct sigaction sa;

    /* TODO 2: Associar a função 'trataSinal' ao campo sa.sa_handler,
       limpar a máscara de sinais (sigemptyset) e colocar sa.sa_flags = 0 */
    sa.sa_handler = trataSinal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    /* TODO 3: Registar o handler para o sinal SIGINT usando sigaction() */
    if (sigaction(SIGINT, &sa, NULL) < 0) {
        perror("Erro no sigaction");
        return EXIT_FAILURE;
    }

    printf("A trabalhar... Pressione Ctrl+C para parar.\n");
    while (!parar) {
        sleep(1);
        printf("Tick...\n");
    }

    /* TODO 4: Imprimir mensagem de despedida limpa quando sair do ciclo */
    printf("Programa terminado com segurança.\n");

    return EXIT_SUCCESS;
}