#!/bin/bash
parentwin=0
childwin=0
for var in {1..100}
do
	echo "Game count: $var"
	cat game.txt
	./memplay game.txt
	./count game.txt
	if [ "$?" -lt "0" ]
	then
		"$parentwin" + "1"
	fi		
	echo "======================"	
done

echo "childwin: count:$childwin"



