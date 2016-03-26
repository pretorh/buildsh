. tests/setup.sh

./buildsh name --max-jobs 8 > $LOG

has_output "make --jobs 8"
