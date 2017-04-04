#!/bin/bash

path=../pdfs/reco
for angle in `seq -f %.2f 20 5 155`
do
	infile=${path}/reco_pdf_3CS_${angle}_cs_avr_spr.root
	root -l -q -b plot_MCP_reco.C"(\"${infile}\")"
done
