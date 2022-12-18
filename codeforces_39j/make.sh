#!/bin/bash

mkdir -p build
pushd build
clang -o main ../src/main.c -Wall -Wextra -Werror -O2 -std=c17
popd