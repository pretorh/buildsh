#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --no-build > "$LOG"

not_has_output "make --jobs"
