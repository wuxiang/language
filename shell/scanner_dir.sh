#!/bin/sh

#function scanDir()
#{
#	echo "sanner $1"
#	workDir=$1
#	cd ${workDir}
#
#	for dirlist in ${ls ${workDir}}
#	do
#		if test -d ${dirlist}
#		then
#			scanDir ${dirlist}
#		else
#			echo ${dirlist}
#		fi
#	done
#}

if test -d $1
then
	echo "hello"
#	scanDir $1
elif test -f $1
then
	echo "you have put file $1, not a directory"
else
	echo "$1 not exist"
fi

for dirlist in $(ls $(pwd))
do
#	if test -d ${dirlist}
#	then
#		scanDir ${dirlist}
#	else
		echo ${dirlist}
#	fi
done
