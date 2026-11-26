#!/bin/bash

if [[ "$#" -ne "1" ]]; then
    echo "Mete um número válido de argumentos" >&2
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "O ficheiro não é válido" >&2
    exit 2
fi

c_files=0
sh_files=0
outros=0

while IFS= read -r linha; do 
    if [[ -z "$linha" ]]; then
        continue
    fi

    case "$linha" in
        *.c | *.h ) 
            c_files=$((c_files + 1))
            ;;
        *.sh )
            sh_files=$((sh_files + 1))
            ;;
        * )
            outros=$((outros+1))
            ;;
    esac
done < "$1"

echo "Total em C: $c_files"
echo "Total em SH: $sh_files"
echo "Outros: $outros"