#!/usr/bin/env bash
set -euo pipefail

g++ -std=c++20 -Wall -Wextra -g -Iinclude src/*.cpp -o tic-tac-toe
./tic-tac-toe
