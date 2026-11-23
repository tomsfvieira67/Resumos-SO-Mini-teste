#!/bin/bash
# verificar.sh - verificação automática do TESTE MODELO (só para treino; no teste real não existe)
# Uso: na pasta onde estão "prova/" e "esperado/":   ./verificar.sh
cd "$(dirname "$0")" || exit 1
export LC_ALL=C
P=prova
T=$(mktemp -d)
pass=0; fail=0

res() {            # res "descrição" código(0=ok)
    if [ "$2" -eq 0 ]; then echo "  [ OK ] $1"; pass=$((pass+1)); else echo "  [FALHA] $1"; fail=$((fail+1)); fi
}
cmp_out() {        # cmp_out "descrição" ficheiro_esperado ficheiro_obtido
    if diff -q "$2" "$3" > /dev/null 2>&1; then res "$1" 0
    else res "$1" 1; diff "$2" "$3" | head -6 | sed 's/^/        /'; fi
}
falha_esperada() { # falha_esperada "descrição" comando...   (deve terminar com código != 0)
    local d=$1; shift
    "$@" > /dev/null 2>&1; [ $? -ne 0 ] && res "$d" 0 || res "$d" 1
}

echo "== Questão 1 (bash) =="
if [ ! -f $P/notas.sh ]; then echo "  notas.sh não encontrado"; fail=$((fail+1)); else
    bash $P/notas.sh $P/notas.txt > $T/o1 2> $T/e1
    cmp_out "stdout sem opções" esperado/notas_normal.txt $T/o1
    grep -q "Aviso: linha ignorada: Hugo 25" $T/e1 && grep -q "Aviso: linha ignorada: Ines 30" $T/e1
    res "avisos em stderr para as linhas inválidas" $?
    bash $P/notas.sh -a $P/notas.txt > $T/o2 2> /dev/null
    cmp_out "stdout com -a" esperado/notas_a.txt $T/o2
    falha_esperada "sem argumentos termina com erro" bash $P/notas.sh
    falha_esperada "ficheiro inexistente termina com erro" bash $P/notas.sh nada_existe.txt
    falha_esperada "opção inválida termina com erro" bash $P/notas.sh -x $P/notas.txt
    falha_esperada "argumentos a mais terminam com erro" bash $P/notas.sh $P/notas.txt $P/notas.txt
fi

echo "== Questão 2 (C sem concorrência) =="
if [ ! -f $P/stock.c ]; then echo "  stock.c não encontrado"; fail=$((fail+1)); else
    gcc -Wall -o $T/stock $P/stock.c 2> $T/cc2
    res "compila" $([ -x $T/stock ] && echo 0 || echo 1)
    [ -s $T/cc2 ] && echo "        (avisos do compilador: $(grep -c warning $T/cc2))"
    if [ -x $T/stock ]; then
        $T/stock $P/stock.txt > $T/o 2>/dev/null;            cmp_out "sem opções" esperado/stock_normal.txt $T/o
        $T/stock -s $P/stock.txt > $T/o 2>/dev/null;         cmp_out "-s" esperado/stock_s.txt $T/o
        $T/stock -m 10 $P/stock.txt > $T/o 2>/dev/null;      cmp_out "-m 10" esperado/stock_m10.txt $T/o
        $T/stock -s -m 10 $P/stock.txt > $T/o 2>/dev/null;   cmp_out "-s -m 10" esperado/stock_s_m10.txt $T/o
        falha_esperada "-m abc termina com erro" $T/stock -m abc $P/stock.txt
        falha_esperada "-m -3 termina com erro" $T/stock -m -3 $P/stock.txt
        falha_esperada "ficheiro inexistente termina com erro" $T/stock nada_existe.txt
        falha_esperada "sem ficheiro termina com erro" $T/stock
        falha_esperada "opção inválida termina com erro" $T/stock -x $P/stock.txt
    fi
fi

echo "== Questão 3 (C com concorrência) =="
if [ ! -f $P/prodcon.c ]; then echo "  prodcon.c não encontrado"; fail=$((fail+1)); else
    gcc -Wall -o $T/prodcon $P/prodcon.c -pthread 2> $T/cc3
    res "compila" $([ -x $T/prodcon ] && echo 0 || echo 1)
    [ -s $T/cc3 ] && echo "        (avisos do compilador: $(grep -c warning $T/cc3))"
    if [ -x $T/prodcon ]; then
        bad=0; hang=0
        for i in $(seq 1 30); do
            timeout 10 $T/prodcon > $T/o 2>/dev/null
            rc=$?
            if [ $rc -eq 124 ]; then hang=$((hang+1)); continue; fi
            s=$(grep '^Consumidor' $T/o | sed 's/.*= //' | awk '{s+=$1} END{print s}')
            if ! grep -qx "Total: 3110 (20 itens)" $T/o || ! grep -qx "Verificacao: OK" $T/o || [ "$s" != "3110" ]; then bad=$((bad+1)); fi
        done
        res "30 execuções sem bloqueios (deadlock): $hang bloqueadas" $([ $hang -eq 0 ] && echo 0 || echo 1)
        res "30 execuções com Total: 3110 (20 itens), Verificacao: OK e somas dos consumidores = 3110: $bad erradas" $([ $bad -eq 0 ] && echo 0 || echo 1)
    fi
    grep -q "RESPOSTA:[[:space:]]*[A-Za-z]" $P/prodcon.c
    res "TODO 5: perguntas teóricas respondidas (confirma o conteúdo no PDF de resolução)" $?
fi
echo
echo "Resultado: $pass verificações OK, $fail falhadas."
echo "(A nota final depende também da qualidade do código; vê a cotação no enunciado.)"
rm -rf "$T"
