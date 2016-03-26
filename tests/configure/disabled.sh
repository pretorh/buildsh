. "$(dirname $0)/../setup.sh"

./buildsh name --no-configure > $LOG

not_has_output "configure"
