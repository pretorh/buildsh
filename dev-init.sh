#!/usr/bin/env bash
set -e

autoreconf -i
./configure
./dev.sh
