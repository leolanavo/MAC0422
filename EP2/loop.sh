#!/bin/bash
i=0
while true; do
	i=$((i+1))
	echo $i
	memusage ./bin/ep2 250 100 20 > /dev/null
done
