. "$(dirname $0)/../setup.sh"

./buildsh name --install-using "echo install1" --install-using "echo install2" > $LOG

not_has_output "make install"
has_output "echo install1"
has_output "echo install2"
