#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
yes "a" | dd bs=1 count=8190 of="$input_file"
if ./buildsh name --source-setup-file "$input_file" > "$LOG" ; then
  error "expected error when total string is too large"
fi
