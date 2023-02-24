. "$(dirname "$0")/../setup.sh"

./buildsh name > "$LOG"

has_output "tar xf name.tar.*"
has_output "cd name"
