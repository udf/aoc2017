#!/bin/bash
export LC_ALL=C
readarray in_offsets < input.txt
length=${#in_offsets[@]}
declare -A offsets
for (( i=0; i< $length; i++)); do
    offsets[$i]=${in_offsets[$i]}
done


ptr=0
steps=0
while ((ptr >= 0 && ptr < length))
do
    jmp=${offsets[$ptr]}
    offsets[$ptr]=$((jmp + (jmp < 3)*2 - 1))
    ptr=$((ptr + jmp))
    ((steps++))
done

echo $steps