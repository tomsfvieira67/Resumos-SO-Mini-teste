#!/bin/bash

# O script recebe exatamente um argumento: o ficheiro com os numeros.
if [[ "$#" -ne 1 ]]; then
    printf 'Uso: %s ficheiro\n' "$0" >&2
    exit 1
fi

file=$1

# Confirma que o argumento e um ficheiro normal e que pode ser lido.
if [[ ! -f "$file" || ! -r "$file" ]]; then
    printf 'Erro: "%s" nao e um ficheiro legivel.\n' "$file" >&2
    exit 1
fi

numbers=()

# Le numeros inteiros separados por espacos ou mudancas de linha.
while IFS= read -r line || [[ -n "$line" ]]; do
    # Remove o CR final, caso o ficheiro use finais de linha Windows.
    line=${line%$'\r'}
    read -r -a fields <<< "$line"

    for token in "${fields[@]}"; do
        # Rejeita valores que nao sejam inteiros decimais.
        if [[ ! "$token" =~ ^-?[0-9]+$ ]]; then
            printf 'Erro: "%s" nao e um numero inteiro valido.\n' "$token" >&2
            exit 1
        fi

        # Converte em base decimal, mesmo quando o numero tem zeros iniciais.
        sign=1
        digits=$token
        if [[ "$digits" == -* ]]; then
            sign=-1
            digits=${digits#-}
        fi
        numbers+=( "$((sign * 10#$digits))" )
    done
done < "$file"

# Um ficheiro vazio ou sem numeros nao pode ser ordenado.
if [[ "${#numbers[@]}" -eq 0 ]]; then
    printf 'Erro: o ficheiro nao contem numeros.\n' >&2
    exit 1
fi

# Selection sort: em cada posicao, procura o menor elemento restante.
for ((i = 0; i < ${#numbers[@]} - 1; i++)); do
    min_index=$i

    for ((j = i + 1; j < ${#numbers[@]}; j++)); do
        if (( numbers[j] < numbers[min_index] )); then
            min_index=$j
        fi
    done

    # Troca o menor elemento encontrado com o elemento da posicao atual.
    if (( min_index != i )); then
        temp=${numbers[i]}
        numbers[i]=${numbers[min_index]}
        numbers[min_index]=$temp
    fi
done

# Mostra o array ordenado; o ficheiro de entrada permanece inalterado.
printf 'Numeros ordenados:\n'
printf '%s\n' "${numbers[@]}"
