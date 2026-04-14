#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usages: $0 <assignment number> <problem number>"
    exit 1
fi

assignment=$(printf "%02d" "$1")
problem=$(printf "%02d" "$2")

assignment_path="assignment-${assignment}/PR-${problem}"
main_file="${assignment_path}/main.c"
input_file="${assignment_path}/input.txt"
test_file="${assignment_path}/output.txt"

problem_binary="AS-${assignment}-PR-${problem}"
stats_file="stats.tmp"

# check if required file exists
for f in "$main_file" "$input_file" "$test_file"; do 
    if [ ! -f "$f" ]; then
        echo "[SCRIPT] Error: $f not found"
        exit 1
    fi
done

# compile and run
echo "[SCRIPT] Compiling..."
gcc -pipe -o2 -std=c11 -o "$problem_binary" "$main_file" -lm || exit 1

echo "[SCRIPT] Running tests..."
echo

./"$problem_binary" "$input_file" "$test_file"

