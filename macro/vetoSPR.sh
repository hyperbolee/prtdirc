#!/bin/bash

# run vetoSPR.C for each trigger/veto cut combination
# trigger 1
# trigger 1 w/o trig1 vetos
# trigger 1 + 2
# trigger 1 + 2 w/o vetos

root -l -q vetoSPR.C"(\"t1\",\"trig1\")" &

root -l -q vetoSPR.C"(\"t12\",\"trig12\")" &

root -l -q vetoSPR.C"(\"t1 && !veto1\",\"trig1!veto\")" &

root -l -q vetoSPR.C"(\"t12 && !veto12\",\"trig12!veto\")" &

wait
