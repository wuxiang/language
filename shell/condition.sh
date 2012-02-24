#!/bin/sh

comparison="float"
#if [ $comparison="integer" ]
if test $comparison="integer"
then 
    echo  "\teq"
else
    echo "=============="
    echo "\tnot eq"
fi

if [ 0=$b ]
then
    echo "0 is true"
else
    echo "0 is false"
fi

if [ 1==0 ]
then
    echo "1 is true"
else
    echo "1 is false"
fi

a=0
if [ "$a" ]
then
    echo "true"
else
    echo "false"
fi

echo "+++++++++++++test equal and not equal++++++++++++++"
a="hello"
b="world"

if [ $a != $b ]
then
    echo "true"
else
    echo "false"
fi

c=

if [ -n "$c"]
then
    echo "true"
else
    echo "false"
fi

e=5
f=7
if [ $e==$f ]
then
    echo "exit true"
else
    echo "exit false"
fi


exit 0
