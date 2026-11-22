#!/bin/bash
function imprime_msg() 
{ 
 echo "A minha primeira funcao" 
 return 0 
} 

function info() {
    echo "$(date)"
    echo "$(hostname)"
    echo "$(whoami)"
}