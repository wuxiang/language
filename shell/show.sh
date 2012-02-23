#! /bin/sh

date
echo "the #hello"
echo 'the #world'
echo the \# here does
echo The#

ch="hello"
echo ${PATH#*:}
#echo $(( 2#101011 ))

{
    local a;
    a = 123;
}
echo $a

exit
