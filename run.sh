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
test_file="${assignment_path}/test.c"

# check if required file exists
if [ ! -f "$main_file" ]; then
    echo "Error: $main_file not found"
    exit 1
fi

if [ ! -f "$input_file" ]; then
    echo "Error: $input_file not found"
    exit 1
fi

if [ ! -f "$test_file" ]; then
    echo "Error: $test_file not found"
    exit 1
fi

# compile and run
gcc -pipe -o2 -std=c11 -o "AS-${assignment}-PR-${problem}" "$main_file" -lm && ./"AS-${assignment}-PR-${problem}"

