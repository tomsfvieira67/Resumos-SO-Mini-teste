#!/bin/bash
remove_prefix=0
if [[ "$1" = "-r" ]]; then
    remove_prefix=1
    shift
fi

if [[ "$#" = 1 ]] ; then
    if [ -d $1 ] ; then
        for f in $1/*; do 
            if [ -f "$f" ]; then
                if [[ "$remove_prefix" = 1 ]]; then
                    name=${f##*/}
                    [[ "$name" == new_* ]] &&
                        mv -- "$f" "${f%/*}/${name#new_}"
                else
                    mv -- "$f" "${f%/*}/new_${f##*/}"
                fi
            fi
        done 
    else
        echo "Diretoria inválida."
        exit 1
    fi
else 
    echo "Só podes ter um argumento!"
    exit 1
fi