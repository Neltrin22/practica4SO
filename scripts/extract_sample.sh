#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Uso: $0 archivo"
    exit 1
fi

archivo="$1"
nombre=$(basename "$archivo")
temp="features/temp_sample.csv"

has_shell=$(grep -qE '^#!' "$archivo" && echo 1 || echo 0)
has_socket=$(grep -aq socket "$archivo" && echo 1 || echo 0)
num_strings=$(strings "$archivo" | wc -l)
exec_size=$(stat -c %s "$archivo")
entropy=$(xxd -p "$archivo" | tr -d '\n' | fold -w2 | \
  awk '{count[$1]++} END {n=0; H=0; for (i in count) {n+=count[i]} for (i in count) {p=count[i]/n; H-=p*log(p)/log(2)} print H}')

echo "$nombre,$has_shell,$has_socket,$num_strings,$exec_size,$entropy,?" > "$temp"
