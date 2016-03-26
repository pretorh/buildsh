. tests/setup.sh

./buildsh name --post "echo hello" > $LOG

has_output "echo hello"
