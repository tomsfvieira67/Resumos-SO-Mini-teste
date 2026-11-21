#!/bin/bash

case $1 in
    [0-9] | [0-9][0-9] ) 
        Message1="O número está no intervalo correto!"
        ;;
    [1-9][0-9][0-9] )
        Message1="O numero não está no intervalo"
        ;;
    * )
        Message1="Não inseriste numero..."
        ;;
esac
echo $Message1

case $2 in 
    sec* )
        Message2="O argumento começa por sec"
        ;;
    * )
        Message2="O argumento não começa por sec"
esac
echo $Message2

    