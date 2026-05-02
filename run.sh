#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usages: $0 <assignment number> <problem number>"
    exit 1
fi

assignment=$(printf "%02d" "$1")
problem=$(printf "%02d" "$2")

problem_dir="assignment-${assignment}/PR-${problem}"
input_file="${problem_dir}/input.txt"
test_file="${problem_dir}/output.txt"

problem_binary="tmp/bin/AS-${assignment}-PR-${problem}"
stats_file="stats.tmp"

# check if required file exists
for f in  "$input_file" "$test_file" \
          "${problem_dir}/problem.c" \
          "${problem_dir}/solver.c"; do 
    if [ ! -f "$f" ]; then
        echo "[SCRIPT] Error: $f not found"
        exit 1
    fi
done

# compile and run
echo "[SCRIPT] Compiling..."
gcc -std=c11 -Wall -Wextra -pipe -o2 \
    framework/driver.c \
    "${problem_dir}/problem.c" \
    "${problem_dir}/solver.c" \
    utils/log.c \
    -Iframework \
    -Iutils \
    -I"${problem_dir}" \
    -o "$problem_binary" -lm || exit 1

echo "[SCRIPT] Running tests..."
echo

./"$problem_binary" "$input_file" "$test_file"

