#!/bin/bash


while [ 1 ]; do
	ps -ef | grep hello.exe| wc > test.file
	n_line=$(awk '(print $1)' test.file)
	echo $n_line
	if [ "$n_line"=="1" ]; then
		echo '[shell] Restarting hello.exe!'
		./hello.exe
	fi
done

