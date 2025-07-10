#!/bin/bash

source ./scripts/utils.sh

extract_features() {
  local folder=$1
  local label=$2
  local output=$3

  echo "filename,has_shell,has_socket,num_strings,exec_size,entropy,label" > "$output"

  for f in "$folder"/*; do
    if [[ -f "$f" ]]; then
      filename=$(basename "$f")
      has_shell=$(has_shell_reference "$f")
      has_socket=$(has_socket_reference "$f")
      num_strings=$(get_num_strings "$f")
      exec_size=$(get_exec_size "$f")
      entropy=$(get_entropy "$f")

      echo "$filename,$has_shell,$has_socket,$num_strings,$exec_size,$entropy,$label" >> "$output"
    fi
  done
}

mkdir -p features

extract_features dataset/benign 0 features/benign.csv
extract_features dataset/malicious 1 features/malicious.csv
