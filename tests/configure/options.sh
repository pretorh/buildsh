#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --configure "option 1" --configure A=B --configure-val X > "$LOG"

has_output "^\./configure.*"
has_output ".*--option 1.*"
has_output ".*--A=B"
has_output ".*X.*"
