#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

input_file=$(create_temp_file)
cat > "$input_file" << EOF
rm $DESTDIR/bin/file
EOF
./buildsh name --post-file "$input_file" > "$LOG"

has_output "rm $DESTDIR/bin/file"
