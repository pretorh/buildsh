. "$(dirname "$0")/../setup.sh"

./buildsh name --test > "$LOG"

has_output "make check"
# paralel
has_output "make check --jobs 4"
