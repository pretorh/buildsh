#!/usr/bin/env bash
set -e

LOG=$(mktemp /tmp/buildsh-XXXXXX)
ERRORS=0

trap 'trap_err ${LINENO}' ERR
trap trap_finalize EXIT

function has_output {
    grep -q "$1" "$LOG" || error "output not found: $1"
    if [ "$(grep --count "$1" "$LOG")" -gt 1 ] ; then
      error "multiple matches found: $1"
    fi
}

function not_has_output {
    if grep -q "$1" "$LOG" ; then
        error "output found: $1"
    fi
}

function has_output_order {
    has_output "$1"
    has_output "$2"

    awk 'found_first==1 {print} /'"$1"'/ {found_first=1}' "$LOG" |
        grep -q "$2" || error "'$2' was not found after '$1'"
}

function error {
    echo "ERROR: $1" 1>&2
    ERRORS=$((ERRORS + 1))
}

function create_temp_file {
  mktemp /tmp/buildsh.tmp-XXXXXX
}

function trap_err {
    error "script error, exit with non-0"
}

function trap_finalize {
    if [ $ERRORS == 0 ] ; then
        exit 0
    else
        echo "$ERRORS errors"
        cat "$LOG"
        exit 1
    fi
}
