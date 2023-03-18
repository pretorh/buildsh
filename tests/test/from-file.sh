#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
cat > "$input_file" << EOF
cd tests
make test
cd ..
EOF
./buildsh name --test-file "$input_file" > "$LOG"

not_has_output "make check"
has_output "cd tests"
has_output "make test"
