#!/bin/bash

function valida_ficheiro() {
    if [[ -f "$1" ]]; then
        local nome="${1##*/}"
        case "$nome" in
            *.c | *.h )
                return 0
                ;;
            * )
                return 2
                ;;
        esac
    else
        return 1
    fi
}

if [[ "$#" -lt 2 ]]; then
    echo "Numero inválido de argumentos" >&2
    exit 1
fi

if [[ ! -d "$1" ]]; then
    echo "A diretoria não existe" >&2
    exit 2
fi

dest="$1"
shift

copiados=()
ignorados=0

for f in "$@"; do
    valida_ficheiro "$f"
    r=$?

    if [[ "$r" -eq 0 ]]; then
        nome_base="${f##*/}"
        cp "$f" "$dest/${nome_base}.bak"
        copiados+=("$nome_base")
    else
        ignorados=$((ignorados + 1))
    fi
done

echo "Total de ficheiros copiados: ${#copiados[@]}"
echo "Lista de copiados: ${copiados[@]}"
echo "Total de ficheiros ignorados: $ignorados"



