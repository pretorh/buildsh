. tests/setup.sh

./buildsh name --config-env ABC=123 > $LOG

has_output "^ABC=123 \./configure$"
