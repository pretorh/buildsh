. "$(dirname $0)/../setup.sh"

./buildsh name --configure-env ABC=123 > $LOG

has_output "^ABC=123 \./configure$"
