#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --configure-dir abc > "$LOG"

has_output "^abc/configure$"
