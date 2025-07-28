make maze

while true; do
    read -p "Enter maze file path: " maze_file
    if [[ -f "$maze_file" ]]; then
        break
    else
        echo "File not found. Please try again."
    fi
done
./maze "$maze_file"