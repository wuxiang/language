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

exit 0
