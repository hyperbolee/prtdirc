#!/bin/bash

# drawFish.sh
# script to draw hit patterns for all
# reconstructed files in a given folder.
# All plots are saved in the fish/
# directory with the naming scheme
# fish_type_study_track.png

study=151
sim=0
for FILE in ../data/${study}/reco/cs/*.root
do
	root -l -q -b drawFish.C"(\"${FILE}\",${sim},${study})" &
done
