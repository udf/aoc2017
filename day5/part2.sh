#!/bin/bash
readarray offsets < input.txt

ptr=0
steps=0
length=${#offsets[@]}
while ((ptr >= 0 && ptr < length))
do
    jmp=${offsets[$ptr]}
    offsets[$ptr]=$((jmp + (jmp < 3)*2 - 1))
    ptr=$((ptr + jmp))
    steps=$((steps + 1))
done

echo $steps