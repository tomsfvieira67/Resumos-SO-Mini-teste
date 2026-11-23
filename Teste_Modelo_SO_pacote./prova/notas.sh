#!/bin/bash
# =====================================================================
# Questão 1 (Bash) - notas.sh                                  [6 valores]
# Uso: ./notas.sh [-a] ficheiro
#
# O ficheiro tem uma linha por aluno: "Nome Nota" (nota inteira 0..20).
# Linhas em branco são ignoradas. Linhas com nota fora do intervalo 0..20
# são ignoradas com o aviso (em stderr):
#       Aviso: linha ignorada: <nome> <nota>
# Opção -a: só mostra os aprovados (nota >= 10), mas a média, o nº de
# aprovados e o melhor aluno consideram TODOS os alunos válidos.
#
# Saída (stdout) para "./notas.sh notas.txt":
#   Ana: 15 (Bom)
#   ...
#   Media: 12.00
#   Aprovados: 5 de 7
#   Melhor: Carla (18)
#
# Completa os blocos TODO. Não alteres o resto.
# =====================================================================

labels=(Reprovado Suficiente Bom Excelente)

# TODO 1 (1 val) - função classifica
# Recebe uma nota em $1 e DEVOLVE (return) um índice para o array labels:
#   0: nota < 10     1: 10 a 13     2: 14 a 17     3: 18 a 20
classifica() {
    case $1 in 
        [0-9] )
            return 0
            ;;
        1[0-3] )
            return 1
            ;;
        1[4-7] )
            return 1
            ;;
        1[8-9] | 20 )
            return 1
            ;;
    esac
}

# TODO 2 (1.5 val) - opção -a e validação de argumentos
# - se existir, a opção -a é sempre o 1.º argumento (ativa soloAprovados=1). Usa $1, $2 e $#
#   (o ficheiro é $2 se houver -a, ou $1 se não houver).
# - tem de haver exatamente 1 argumento além da opção -a; senão, mensagem de uso em stderr
#   e exit 1. O ficheiro tem de existir e ser um ficheiro normal (senão, mensagem em stderr
#   e exit 1).
soloAprovados=0
if [[ "$#" -gt "2" ]]; then
    echo "Introduz um número válido de argumentos" >&2
    exit 1
fi 

if [[ "$1" == "-a" ]]; then
    soloAprovados=1
else
    soloAprovados=0
fi
# TODO 3 (1.5 val) - leitura do ficheiro para os arrays nomes e notas
# Guarda só as linhas válidas (ver regras no cabeçalho). Podes assumir que a nota, quando
# existe, é um número inteiro.
# Se não houver nenhuma linha válida: escrever "Sem dados validos" em stderr e exit 1.
nomes=()
notas=()
if [[ -f "$1" ]]
    while IFS= read -r nome nota; do
        if [[ "$nota" -gt "20" ]] || [[ "$nota" -lt "0" ]]; then
            echo "Nota inválida!" >&2
            exit 1
        else 
            nomes+=("$nome")
            notas+=("$nota")
        fi
    done < "$1"

if [[ -f "$2" ]]
    while IFS= read -r nome nota; do
        if [[ "$nota" -gt "20" ]] || [[ "$nota" -lt "0" ]]; then
            echo "Nota inválida!" >&2
            exit 1
        else 
            nomes+=("$nome")
            notas+=("$nota")
        fi
    done < "$2"
total=${#nomes[@]}

# TODO 4 (1.5 val) - ciclo principal
# Para cada aluno: chamar classifica, acumular a soma das notas, contar os aprovados,
# registar o índice do melhor aluno e imprimir "Nome: nota (Classificação)"
# (ou saltar a impressão se -a e a nota < 10).
soma=0
aprov=0
melhor=0
count=0
# ... completa ...
for aluno in nomes; do
    classifica() ${notas[count]}
    r=$?
    if [[ "$r" -eq "1" ]]; then
        aprov=$((aprov + 1))
        soma=$((soma + notas[count]))
        echo "$aluno nota: ${notas[count]}"
        if [[ "${notas[count]}" -gt "${notas[count - 1]}" ]]; then
            melhor=${notas[count]}
        fi
    else
        soma=$((soma + notas[count]))
    fi
    count=((count + 1))
    if [[ "$count" -eq "$total" ]]; then
        break
    fi 
done
    


# TODO 5 (0.5 val) - resumo (formato exato do cabeçalho; média com 2 casas decimais)
# ... completa ...
