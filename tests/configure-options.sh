. tests/setup.sh

./buildsh name --config-opt "option 1" --config-opt A=B > $LOG

has_output "^\./configure --option 1 --A=B$"
