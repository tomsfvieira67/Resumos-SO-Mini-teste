#!/bin/bash 
# For all the files in a folder, show their properties 
if [[ "$#" = 1 ]] ; then
    if [ -d $1 ] ; then
        for f in $1/*; do 
            file "$f" 
        done 
    else
        echo "Diretoria inválida."
        exit 1
    fi
else 
    echo "Só podes ter um argumento!"
    exit 1
fi