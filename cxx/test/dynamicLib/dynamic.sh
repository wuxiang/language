#!/bin/sh

g++ -c -fPIC $1 -o$2
g++ -shared $2 -o$3
exit 0
