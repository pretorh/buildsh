#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
cat > "$input_file" << EOF
make prog1
make prog2
EOF
./buildsh name --build-file "$input_file" > "$LOG"

has_output "make prog1"
has_output "make prog2"
not_has_output "make --jobs"
