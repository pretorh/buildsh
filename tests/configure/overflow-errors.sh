#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
yes "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTU" | dd bs=1 count=8190 of="$input_file"
if ./buildsh name --configure-using "echo configure1" --configure-file "$input_file" --configure-using "echo configure2" > "$LOG" ; then
  error "expected error when total string is too large"
fi

not_has_output "configure2"
