#!/bin/bash

func(){
    for II in $(seq $1 $2)
    do
        SS=$(printf "%4d" $II)
        echo -ne "\e[38;5;"0";48;5;"$II"m"
        echo -ne "$SS"
    done
    echo ""
}

V=0

for JJ in $(seq 0 15)
do
    func $V $((V+15)) && V=$((V+16))
done
echo -ne "\e[0m"


