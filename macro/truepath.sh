#!/bin/bash

# run root script truePath.C for all
# reconstruction files of a given type
# (full or avg LUT) in a given directory

# most useful function eva
start_time=$(date +%s)
waitForMe ()
{
    while : 
    do 
		activth=$(ps aux | grep "root.exe.*[t]ruePath" | wc -l)
		printf "\r$statusline [$activth threads running] ---- [$(($(date +%s) - start_time)) s] "
		sleep .1
		if [ "$activth" -lt "$1" ]; then 
			break  
 		fi
    done
}

luttype=full
path=../simulation/151/reco

for FILE in ${path}/*${luttype}_spr.root
do
	root -l -q -b truePath.C"(\"${FILE}\",\"${luttype}\")" >> /dev/null &

	waitForMe 4
done
