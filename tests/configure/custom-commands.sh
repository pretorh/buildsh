#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --configure-using "echo configure1" --configure-using "echo configure2" > "$LOG"

not_has_output "./configure"
has_output "echo configure1"
has_output "echo configure2"
