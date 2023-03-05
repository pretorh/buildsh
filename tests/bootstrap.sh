#!/usr/bin/bash
set -e
. "$(dirname "$0")/setup.sh"

test_dir=$(mktemp -d /tmp/buildsh-XXXXXX)
bootstrap=$(realpath "$(dirname "$0")/../bootstrap.sh")
cp ./buildsh-*.tar.gz "$test_dir/"

echo "running $bootstrap for test" >&2
(
  cd "$test_dir"
  $bootstrap
) >> "$LOG" || error "bootstrap script failed"

test -x "$test_dir"/buildsh || error "buildsh not created in $test_dir"
test -f "$test_dir/bootstrap.log" || error "bootstrap log file not created"
if [ "$(find "$test_dir" | wc -l)" -ne 4 ] ; then
  ls -1 "$test_dir" "" >> "$LOG"
  error "unexpected files in $test_dir after buildsh created"
fi
