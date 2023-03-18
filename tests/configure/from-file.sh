#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
cat > "$input_file" << EOF
./config
EOF
./buildsh name --configure-file "$input_file" > "$LOG"

has_output "./config"
not_has_output "./configure"
