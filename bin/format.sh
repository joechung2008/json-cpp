#!/bin/bash

# Format all .cpp and .hpp files in the project using clang-format
# Exclude build and out directories
find . -path ./build -prune -o -path ./out -prune -o -name "*.cpp" -print -o -name "*.hpp" -print | xargs clang-format -i

echo "Formatting complete."