#!/bin/bash

num1=5
num2=10

if [ "$1" -lt "$num1" ] ; then
    echo "$1 é menor que $num1"

elif [ "$1" -gt "$num2" ] ; then
    echo "$1 é maior que $num2"
else
    echo "$1 é maior que 5 e menor que 10"
fi
