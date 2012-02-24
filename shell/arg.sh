#!/bin/sh

until [ -z "$1"]
do
    echo -n "$1"
    shift
done
echo

a=100
echo '$a'
echo "'$a',$a"
echo "============================"
b=888
echo "${b-2}"

unset variable

echo "${variable-2}"

char="hello"
echo "${char-4}"
n=
num=$((n = 5+3))
com=$(ls -l)

echo $num
echo
echo $n
#echo $com

exit 0
