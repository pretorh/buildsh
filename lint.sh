#!/usr/bin/env bash
set -e

shellcheck --source-path=SCRIPTDIR --format=gcc ./tests/setup.sh ./tests/**/*.sh
