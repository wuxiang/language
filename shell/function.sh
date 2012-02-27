#!/bin/sh


greet()
{
    echo "hello world"
}

func()
{
    if [ -z "$1" ]
    then
        echo "the number of arguement is zero"
    else
        echo "$1"
    fi
}

max()
{
    if [ -z "$2" ]
    then
        return $E_PARAM_ERR
    fi

    if [ "$s1" -eq "$2" ]
    then
        return $EQUAL
    else
        if [ "$1" -gt "$2" ]
        then
            return $1
        else
            return $2
        fi
    fi

}

greet
func ""
func "hello"
max 10 20
return_max=$?
echo $return_max

exit 0
