#!/bin/bash

function num_comp() {
    if [ "$n1" -eq "$n2" ] ; then
        Message="Os numeros são iguais"
    elif [ "$n1" -gt "$n2" ] ; then
        Message="$n1 é maior que $n2"
    else
        Message="$n1 é menor que $n2"
    fi 
}

read -p "Introduza o primeiro numero: " n1
read -p "Introduza o segundo numero: " n2
num_comp "$n1" "$n2"
echo "$Message"