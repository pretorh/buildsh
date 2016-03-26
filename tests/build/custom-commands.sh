. "$(dirname $0)/../setup.sh"

./buildsh name --build-using "echo build1" --build-using "echo build2" > $LOG

not_has_output "make --jobs"
has_output "echo build1"
has_output "echo build2"
