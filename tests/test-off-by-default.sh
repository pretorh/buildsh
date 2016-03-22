. tests/setup.sh

./buildsh name > $LOG

not_has_output "make check"
