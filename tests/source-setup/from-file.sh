#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
cat > "$input_file" << EOF
patch 1
patch 2
EOF
./buildsh name --source-setup-file "$input_file" > "$LOG"

has_output "patch 1"
has_output "patch 2"
