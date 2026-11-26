#!/bin/bash

if [[ "$#" -ne "2" ]]; then
    echo "Número inválido de argumentis" >&2
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "Ficheiro inválido ou não existe" >&2
    exit 1
fi

countOK=0
countERRO=0
countAVISO=0
outros=0
lentos=()
while IFS=':' read -r user estado tempo; do
    if [[ -z "$user" ]]; then
        continue
    fi

    case "$estado" in 
        OK )
            countOK=$((countOK + 1))
            ;;
        ERRO )
            countERRO=$((countERRO + 1))
            ;;
        AVISO )
            countAVISO=$((countAVISO + 1))
            ;;
        * )
            outros=$((outros + 1))
            ;;
    esac

    if [[ "$tempo" -gt "$2" ]]; then
        lentos+=("$user")
    fi
done < "$1"

echo "Estado OK: $countOK"
echo "Estado ERRO: $countERRO"
echo "Estado AVISO: $countAVISO"
echo "Outros: $outros"

if [[ ${#lentos[@]} -gt "0" ]]; then 
    printf "%s\n" "${lentos[@]}" | sort -u
else
    echo "Não há utilizadores lentos"
fi