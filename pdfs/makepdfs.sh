#!/bin/bash

for norm in 1 2 3 4
do
	for smooth in 0 1
	do
		root -l -q -b ../macro/loadlib.C createPDFs_2.C+"(${norm},${smooth})"
	done
done

