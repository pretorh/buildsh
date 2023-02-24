#!/usr/bin/env bash
set -e

clear
rm -f "test-suite.log"
make
make check || (cat "test-suite.log" && exit 1)
