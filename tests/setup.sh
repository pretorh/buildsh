LOG=$(mktemp /tmp/buildsh-XXXXXX)
ERRORS=0

trap 'trap_err ${LINENO}' ERR
trap trap_finalize EXIT

function has_output {
    cat $LOG | grep -q "$1" || error "output not found: $1"
}

function not_has_output {
    if cat $LOG | grep -q "$1" ; then
        error "output found: $1"
    fi
}

function error {
    echo "ERROR: $1" 1>&2
    ERRORS=$((ERRORS + 1))
}

function trap_err {
    error "script error, exit with non-0"
}

function trap_finalize {
    if [ $ERRORS == 0 ] ; then
        exit 0
    else
        echo "$ERRORS errors"
        cat $LOG
        exit 1
    fi
}
