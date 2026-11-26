#!/bin/bash

# Exige pelo menos uma opcao para apresentar no menu.
if [[ "$#" -eq 0 ]]; then
    echo "Indica pelo menos uma opcao para o menu." >&2
    exit 1
fi

# PS3 define a mensagem apresentada por select antes de cada escolha.
PS3="Escolhe uma opcao: "

# Cada argumento passado ao script aparece como uma opcao do menu.
select arg in "$@"; do
    # Se a escolha for invalida, select deixa arg vazio.
    if [[ -z "$arg" ]]; then
        echo "Opcao invalida; a terminar." >&2
        exit 1
    fi

    # REPLY contem o numero digitado e arg contem a opcao correspondente.
    printf 'Escolheste %s (%s).\n' "$arg" "$REPLY"
done
