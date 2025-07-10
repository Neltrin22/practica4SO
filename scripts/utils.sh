#!/bin/bash

has_shell_reference() {
  strings "$1" | grep -q "/bin/sh" && echo 1 || echo 0
}

has_socket_reference() {
  strings "$1" | grep -iq "socket" && echo 1 || echo 0
}

get_num_strings() {
  strings "$1" | wc -l
}

get_exec_size() {
  stat -c %s "$1"
}

get_entropy() {
  hexdump -v -e '1/1 "%02X"' "$1" | \
  fold -w2 | sort | uniq -c | \
  awk '{
    counts[NR] = $1;
    total += $1;
  }
  END {
    sum = 0;
    for (i = 1; i <= NR; i++) {
      p = counts[i] / total;
      sum += p * log(p) / log(2);
    }
    if (total > 0) {
      print -sum;
    } else {
      print 0;
    }
  }'
}

