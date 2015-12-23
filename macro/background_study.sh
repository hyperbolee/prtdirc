# run background.C for each file in ../data/7GeVscans

RUN=../data/7GeVscans/*.root

for f in ${RUN}
do
	echo ${f}
done
