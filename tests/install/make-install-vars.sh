#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --make-install prefix=/usr --make-install foo=bar > "$LOG"

has_output "^make prefix=/usr foo=bar install"
