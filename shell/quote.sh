#!/bin/sh

#hello="hello, world"
#echo $hello
#echo ${hello}
#
#echo "=================="
#
#echo "$hello="hhhh""
#echo "${hello}"

hello=
echo "\$hello(nullvalue)=$hello"

uninitialize=23
unset uninitialize
echo "uninitialize =  $uninitialize"

set "uninitialize += 10"
echo "$uinitialize"

exit 0

