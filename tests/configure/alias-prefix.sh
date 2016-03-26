. "$(dirname $0)/../setup.sh"

./buildsh name --configure-prefix X > $LOG

has_output "^\./configure --prefix=X$"
