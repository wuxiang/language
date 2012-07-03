#!/bin/bash

scanDir()
{
	#for dirlist in ${workDir}
	for dirlist in $(ls $1)
	do
		if test -d ${dirlist}
		then
            dir="$1/$dirlist"
            cd ${dir}
		    scanDir ${dir}
            cd ..
		else
			echo "hello-${dirlist}"
		fi
	done
}

function aun1
{
    echo "hello"
}

if test -d $1
then
    cd $1
	scanDir $1
elif test -f $1
then
	echo "you have put file $1, not a directory"
else
	echo "$1 not exist"
fi

#for dirlist in $(ls $(pwd))
#do
#	if test -d ${dirlist}
#	then
#		scanDir ${dirlist}
#	else
#		echo ${dirlist}
#	fi
#done
