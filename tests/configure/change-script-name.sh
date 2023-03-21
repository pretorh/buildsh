#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

./buildsh name --configure-script-name "ConfScriptName" > "$LOG"

not_has_output "^\./configure$"
has_output "^\./ConfScriptName$"

./buildsh name --configure-dir abc --configure-script-name "ConfScriptName" > "$LOG"

not_has_output "^\./configure$"
has_output "^abc/ConfScriptName$"
