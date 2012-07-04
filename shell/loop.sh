#!/bin/bash

for i in 1 2 3 4 5
do
    echo $i
done

file="./condition.sh"
for j in $file
do
    echo $j
done

#LIMIT=10
#for ((a=1; $a <= $LIMIT ; ))
#do 
#    echo $a;
#done

#c=1
#while [[ $c -le 5 ]]
#do
#    echo "Welcome $c times"
#        (( c++ ))
#done

c=1
while [ $c -le 5 ]
do
    echo "Welcone $c times"
        (( c++ ))
done
echo

limit=10
for((a=1,b=1; a<=limit; a++, b++))
do
    echo -n "$a-$b"
    echo '\t'
done
echo
