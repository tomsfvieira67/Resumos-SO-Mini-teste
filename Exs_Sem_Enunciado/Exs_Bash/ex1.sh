#!/bin/bash

if [ "$#" -eq "0" ]; then
    echo "Tens de introduzir um ou vários diretórios!"
    exit 1
fi

for dir in "$@"; do
    if [[ -d "$dir" ]]; then
        for f in "$dir"/*; do
            if [[ -f "$f" ]]; then
                echo "O teu ficheiro existe"
                [ -w "$f" ] && echo "$f Tem Permissão de escrita"
                [ -r "$f" ] && echo "$f Tem Permissão de leitura"
                [ -x "$f" ] && echo "$f Tem Permissão de (não me lembro)"
            else
                echo "O teu ficheiro não existe"
                exit 1
            fi
        done
    else
        echo "Diretoria inválida"
        exit 1
    fi
done