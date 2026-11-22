#!/bin/bash 
function numeric_to_string() 
{ 
    # A funcao continua a apresentar o texto correspondente ao argumento.
    case "$1" in 
        1) 
            echo "Um" 
            ;; 
        2) 
            echo "Dois" 
            ;; 
        3) 
            echo "Três" 
            ;; 
        *) 
            echo "Outro numero" 
    esac 

    # O codigo de retorno da funcao passa a ser o numero recebido.
    # Em Bash, o valor de retorno tem de estar entre 0 e 255.
    return "$1"
} 

# Chama a funcao com o primeiro argumento do script.
numeric_to_string "$1"

# Guarda $? imediatamente: qualquer comando entre a chamada e esta linha
# substituiria o valor de retorno da funcao.
valor_devolvido=$?
echo "Valor devolvido pela funcao: $valor_devolvido"