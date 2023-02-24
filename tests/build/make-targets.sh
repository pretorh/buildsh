. "$(dirname "$0")/../setup.sh"

./buildsh name --make abc --make def > "$LOG"

has_output "^make --jobs .* abc def"
