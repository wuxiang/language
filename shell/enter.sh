#!/bin/bash

a='\n'
b="\n"
c='\r'
d="\r"

echo "begin"
#echo -n $a
#echo -n $b
#echo -n $c
read -N1 in
if [ $in = "\n" ]
then
    echo "huiche"
else
    echo "not"
    echo $in
fi
echo "end"
