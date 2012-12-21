#!/bin/sh

#file=./1.txt
#{
#    read line1
#    read line2
#} < $file
#
#echo "first line in $file is: "
#echo "$line1"
#
#echo "second line in $file is: "
#echo "$line2"

filename=$1
while read line
do
echo $line
done <$filename

exit 0
