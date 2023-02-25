#!/usr/bin/env bash
set -e

shellcheck --source-path=SCRIPTDIR --format=gcc \
  ./*.sh ./tests/setup.sh ./tests/**/*.sh
