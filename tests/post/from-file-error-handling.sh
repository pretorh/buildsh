#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
rm "$input_file"
if ./buildsh name --post-file "$input_file" > "$LOG" ; then
  error "should have failed for file not found"
fi

input_file=$(create_temp_file)
yes "a" | dd of="$input_file" bs=4k count=10000
echo "end of larger file" >> "$input_file"
if ./buildsh name --post-file "$input_file" > "$LOG" ; then
  error "should have failed for very large file"
fi
