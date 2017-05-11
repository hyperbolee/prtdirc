#!/bin/bash

statusline="Generating Plots"
start_time=$(date +%s)
waitForMe (){
    while : 
    do 
	activth=$(ps aux | grep "root.exe" | grep "plot_spr_3" | wc -l)
	printf "\r$statusline [$activth] ---- [$(($(date +%s) - start_time)) s] "
	sleep .1
	if [ "$activth" -lt "$1" ]; then 
	    break  
	fi
    done
}  

data=../data/151/reco/cs
for FILE in ${data}/*_spr.root; do
	root -l -b -q plot_spr_3.C"(\"${FILE}\")" >> /dev/null &
	
	waitForMe 3
done

waitForMe 1

printf "\n$statusline [$activth] ---- [-]\n"

hadd -f analysis/analysis.root $(ls analysis/analysis_*.root | sort -n -t _ -k 2)
rm analysis/analysis_*.root

