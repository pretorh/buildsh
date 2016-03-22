. tests/setup.sh

./buildsh name --test="echo abc" --test="echo def" > $LOG

not_has_output "make check"
has_output "echo abc"
has_output "echo def"
