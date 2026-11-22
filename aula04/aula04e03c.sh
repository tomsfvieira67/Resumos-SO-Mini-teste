#!/bin/bash 
# Cria um array associativo: os elementos sao identificados por chaves de texto.
declare -A assArray 
 
# Associa valores as chaves Aveiro e Porto.
assArray[Aveiro]=10 
assArray[Porto]=NA 
# Acrescenta ao array associativo a chave Lisboa com o valor 5.
assArray+=([Lisboa]=5) 
 
# ${assArray[@]} expande para todos os valores guardados no array.
echo vals  ${assArray[@]} 
# ${#assArray[@]} devolve a quantidade de elementos do array.
echo count ${#assArray[@]} 
# ${!assArray[@]} expande para todas as chaves do array.
echo index ${!assArray[@]} 
 
# Acede diretamente ao valor associado a chave Lisboa.
echo val Lisboa ${assArray[Lisboa]} 