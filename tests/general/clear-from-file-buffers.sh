#!/usr/bin/env bash
set -e

. "$(dirname "$0")/../setup.sh"

source_setup_file=$(create_temp_file)
cat > "$source_setup_file" << EOF
patch -Np1 -i ../dummy.patch
EOF

config_file=$(create_temp_file)
cat > "$config_file" << EOF
./config --qwe
EOF

build_file=$(create_temp_file)
cat > "$build_file" << EOF
make target1
make target2
EOF

test_file=$(create_temp_file)
cat > "$test_file" << EOF
make test1
make test2
EOF

install_file=$(create_temp_file)
cat > "$install_file" << EOF
make inst prog1
make inst prog2
EOF

post_file=$(create_temp_file)
cat > "$post_file" << EOF
mv foo bar
EOF

./buildsh name \
  --source-setup-file "$source_setup_file" \
  --configure-file "$config_file" \
  --build-file "$build_file" \
  --test-file "$test_file" \
  --install-file "$install_file" \
  --post-file "$post_file" \
  > "$LOG"

expected="${0/sh/expected.out}"
diff --unified "$expected" "$LOG"
