. "$(dirname $0)/../setup.sh"

./buildsh name --sudo > $LOG

has_output "sudo make install"
