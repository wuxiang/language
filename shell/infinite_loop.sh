#! /bin/sh

for i in 1 2 3 4 5 6 7 8 9 10
do
    echo -n "$i"
done&

echo "hello"

sleep 10&

for i in 11 12 13 14 15 16 17 18 19 20
do
    echo -n "$i"
done

echo "world"

exit 0
