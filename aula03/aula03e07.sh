#!/bin/bash 
# Calculate the sum of a series of numbers. 
SCORE="0" 
SUM="0" 
AVG="0"
COUNT="0"
num1=1
while true; do 
    echo -n "Enter your score [0-10] ('q' to quit): " 
    read SCORE; 
    if (("$SCORE" < "0"))  || (("$SCORE" > "10")); then 
        echo "Try again: " 
    elif [[ "$SCORE" == "q" ]]; then 
        echo "Sum: $SUM." 
        break 
    elif [[ "$SCORE" == "r" ]] ; then 
        echo "Reiniciar valores..."
        SUM=0
        AVG=0
        COUNT=0
    else 
        SUM=$((SUM + SCORE))
        COUNT=$((COUNT + num1))
    fi 
done 
AVG=$((SUM / COUNT))
echo "Media: $AVG."
echo "Exiting."