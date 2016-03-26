. "$(dirname $0)/../setup.sh"

./buildsh name --configure "option 1" --configure A=B --configure-val X > $LOG

has_output "^\./configure --option 1 --A=B X$"
