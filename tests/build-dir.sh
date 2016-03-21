. tests/setup.sh

./buildsh name --build-outside-sources > $LOG

has_output "mkdir build"
has_output "cd build"

# cleanup from 2 dirs up (need to cd out of build first)
has_output "cd ../../"
has_output "rm -rf name"
