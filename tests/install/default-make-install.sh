#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name > "$LOG"

has_output "make install"
