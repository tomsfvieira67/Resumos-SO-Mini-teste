#!/bin/bash 
# This script checks the existence of a file 
echo "Checking..." 

if [ "$#" -ne 1 ] ; then
    echo "Precisa de inserir um argumento depois de $0"
    exit 1
fi

if [[ -f $1 ]] ; then 
    echo "$1 existe e é um ficheiro." 

elif [[ -d $1 ]] ; then
    echo "$1 existe e é uma diretoria"

    [ -r "$1" ] && echo "Tem permissão de leitura"
    [ -w "$1" ] && echo "Tem permissão de escrita"
    [ -x "$1" ] && echo "Tem permissão de acesso/execução"

else 
    echo "$1 não existe" 
fi 
echo "...done." 