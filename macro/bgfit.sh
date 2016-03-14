#!/bin/bash

# run root script bgfit.C for all
# reconstruction files with full LUT
# in a given directory

# most useful function eva
statusline="bg fits"
start_time=$(date +%s)
waitForMe ()
{
    while : 
    do 
		activth=$(ps aux | grep "root.exe.*[b]gfit" | wc -l)
		printf "\r$statusline [$activth threads running] ---- [$(($(date +%s) - start_time)) s] "
		sleep .1
		if [ "$activth" -lt "$1" ]; then 
			break  
 		fi
    done
}

path=../simulation/151/reco
for FILE in ${path}/*full_spr.root
do
	root -l -q -b bgfit.C"(\"${FILE}\")" >> /dev/null &

	waitForMe 4
done
wait

hadd -f bgfit_norm.root bgfit_*.root
rm bgfit_*0.root
rm bgfit_*5.root
