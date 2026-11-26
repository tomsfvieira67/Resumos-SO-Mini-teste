#!/bin/bash

if [[ "$#" -ne "2" ]]; then
    echo "Introduz um número válido de argumentos" >&2
    exit 1
fi

if [[ "$2" -lt "0" ]] || [[ "$2" -gt "20" ]]; then
    echo "Nota inválida!" >&2
    exit 2
fi

cNormal=0
cRecurso=0
cEspecial=0
outros=0
aprovados=()
soma_notas=0
media=0

while IFS=':' read -r nome nota estado; do
    if [[ -z "$nome" ]]; then
        continue
    fi

    case $estado in 
        NORMAL )
            cNormal=$((cNormal + 1))
            ;;
        RECURSO )
            cRecurso=$((cRecurso + 1))
            ;;
        ESPECIAL )
            cEspecial=$((cEspecial + 1))
            ;;
        * )
            outros=$((outros + 1))
            ;;
    esac 

    if [[ "$nota" -eq "$2" ]]; then
        aprovados+=("$nome")
        soma_notas=$((soma_notas + nota))
    fi 
done < "$1"

echo "Normal: $cNormal"
echo "Recurso: $cRecurso"
echo "Especial: $cEspecial"
echo "Outros: $outros"

if [[ ${#aprovados[@]} -gt "0" ]]; then
    media=$((soma_notas / ${#aprovados[@]}))
    printf "%s\n" "${aprovados[@]}" | sort -u
    echo "Media: $media"
else
    echo "Nenhum aluno aprovado."
fi



