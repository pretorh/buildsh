. tests/setup.sh

./buildsh name --config-dir abc > $LOG

has_output "^abc/configure$"