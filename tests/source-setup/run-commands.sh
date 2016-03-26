. tests/setup.sh

./buildsh name --source-setup "echo hello" > $LOG

has_output "echo hello"
