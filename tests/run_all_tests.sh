#!/usr/bin/env bash
# Run all test executables in this directory
set -e
for exe in $(find . -maxdepth 1 -type f -executable -name 'test_*'); do
    echo "Running $exe..."
    $exe
    echo
    echo "----------------------"
done
