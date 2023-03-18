#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
cat > "$input_file" << EOF
make inst prog1
EOF
./buildsh name --install-file "$input_file" > "$LOG"

has_output "make inst prog"
not_has_output "make install"
