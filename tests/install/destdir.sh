#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

DESTDIR=qwe/ ./buildsh name > "$LOG"

has_output "make DESTDIR=qwe/ install"
