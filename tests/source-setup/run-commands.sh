#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --source-setup "echo hello" > "$LOG"

has_output "echo hello"

has_output_order "tar" "echo hello"
