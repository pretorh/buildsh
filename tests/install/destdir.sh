. "$(dirname $0)/../setup.sh"

./buildsh name --destdir qwe/ > $LOG

has_output "make DESTDIR=qwe/ install"
