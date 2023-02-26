#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --post "echo hello" > "$LOG"

has_output "echo hello"
