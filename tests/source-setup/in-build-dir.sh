#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --build-dir-setup="echo in-build-dir" > "$LOG"

has_output "^echo in-build-dir$"
# implies build dir
has_output "cd \$BUILD_DIR"

# source setup, then cd build dir, then build-dir-setup
./buildsh name --source-setup="echo source-setup" --build-dir-setup="echo in-build-dir" > "$LOG"

has_output_order "echo source-setup" "BUILD_DIR="
has_output_order "BUILD_DIR=" "echo in-build-dir"
