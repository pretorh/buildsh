. "$(dirname "$0")/../setup.sh"

./buildsh name --archive Name.tar.xz > "$LOG"

# archive name is different from the dir name
has_output "tar xf Name.tar.xz"
has_output "cd name"
