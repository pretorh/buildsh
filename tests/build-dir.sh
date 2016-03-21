. tests/setup.sh

./buildsh name --build-outside-sources > $LOG

has_output "mkdir build"
has_output "cd build"
