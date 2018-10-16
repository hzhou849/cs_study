#! /bin/bash

if [[ $1 ]] && [[ $2 ]]; then
	echo $1 $2
	sh -c "gcc -Wall -pedantic $1 -o $2"
else
	echo "usage: 'compile <input_file> <output_file>'"
	exit
fi

