. "$(dirname $0)/../setup.sh"

./buildsh name --config-opt "option 1" --config-opt A=B --config-val X > $LOG

has_output "^\./configure --option 1 --A=B X$"
