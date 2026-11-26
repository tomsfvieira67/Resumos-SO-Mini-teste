#!/bin/bash

function classifica_ficheiro() {
    # TODO 1: Extrair apenas o nome do ficheiro (sem o caminho da diretoria) usando Parameter Expansion
    local nome=${file##*/}

    # TODO 2: Completar a estrutura case sobre "$nome":
    #   - *.log ou *.txt -> return 0
    #   - temp_*         -> return 1
    #   - outros         -> return 2
    case "$nome" in
        *.log | *.txt )
            return 0
            ;;
        temp_* )
            return 1
            ;;
        * )
            return 2
            ;;
    esac
}

# TODO 3: Validar se o número de argumentos é menor que 2 OU se $1 não é uma diretoria
if [[ "$#" -lt "2" ]] || [[ ! -d "$1" ]]; then
    echo "Uso: $0 <dir_destino> <fich1> [fich2 ...]" >&2
    exit 1
fi

dest="$1"
shift # Remove $1, deixando em "$@" apenas os ficheiros a processar
ignorados=()

# TODO 4: Iterar sobre todos os argumentos restantes em "$@" (preservando espaços nos nomes)
for f in "$@"; do
    if [[ ! -f "$f" ]]; then
        echo "Aviso: '$f' não é um ficheiro regular."
        continue
    fi

    classifica_ficheiro "$f"
    # TODO 5: Guardar o código de retorno da função numa variável 'ret'
    ret=$?

    if [[ $ret -eq 0 ]]; then
        cp "$f" "$dest/"
        echo "Copiado: $f"
    elif [[ $ret -eq 2 ]]; then
        ignorados+=("$f")
    fi
done

# TODO 6: Imprimir o número total de elementos no array 'ignorados' e listar todos os seus elementos
echo "Total de ficheiros não classificados: ${#ignorados[@]}"
echo "Lista: ${ignorados[@]}"