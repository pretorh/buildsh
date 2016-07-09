. "$(dirname $0)/../setup.sh"

./buildsh name --build-outside-sources > $LOG

has_output "BUILD_DIR=\$(mktemp -d ./buildsh-build-XXXXX)"
has_output "cd \$BUILD_DIR"

# run configure in parent dir
has_output "^\../configure$"

# cleanup from 2 dirs up (need to cd out of build first)
has_output "cd ../.."
has_output "rm -rf name"
