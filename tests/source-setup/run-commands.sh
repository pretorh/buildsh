#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --source-setup "echo hello" > "$LOG"

has_output "echo hello"
