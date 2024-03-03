#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --make prefix=/usr --make foo=bar > "$LOG"

has_output "^make --jobs .*  prefix=/usr foo=bar"
