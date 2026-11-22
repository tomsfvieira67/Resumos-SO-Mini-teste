#!/bin/bash

nota_minima=10
sum=0
count=0
avg=0

if [[ "$#" -ne "2" ]]; then
    echo "Tens de meter dois argumentos!" 
    exit 1
fi

if [[ ! -f "$1" ]]; then
    echo "O primeiro argumento tem de ser um ficheiro!"
    exit 2
fi

case $2 in
    [0-9] | 1[0-9] | 20 )
    nota_minima=$2
        Message="Nota válida"
        ;;
     )
        Message="Nota inválida!"
        ;;
esac
if [ "$Message" == "Nota inválida!" ]; then
    echo "$Message"
    exit 3
fi

echo "$Message"

while IFS= read -r aluno nota; do
    if [ "$nota" -ge "$nota_minima" ]; then
        aprovados+=("$aluno")
        count=$((count + 1))
        sum=$((sum + nota))
    fi
done < "$1"

echo "Numero de aprovados ${#aprovados[@]}"
echo "Aprovados: ${aprovados[@]}"

if [[ "${#aprovados[@]}" -ge "1" ]]; then
    avg=$((sum / count))
    echo "A media das notas é $avg"
else
    echo "Nenhum aprovado"
fi
