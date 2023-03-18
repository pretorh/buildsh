#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name > "$LOG"

has_output "cd \.\."
has_output "rm -rf name"
