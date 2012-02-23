#!/bin/sh

a=23
echo $a
b=a
echo b

c=$(ls -l)
echo "$c"

d='date'
echo "$d"

m=2334
set "m+=1"
echo "$m"

echo "operator="
x=888888
y=$x
echo $y

exit 0
