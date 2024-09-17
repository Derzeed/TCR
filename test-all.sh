#! /usr/bin/env nix-shell
#! nix-shell -i bash -p gcc

set -euo pipefail
IFS=$'\n\t'

SRCS=(
    "./Graph/Single-source-shortest-path/dijkstra.cpp"
    "./Graph/Single-source-shortest-path/bellman-ford.cpp"
)

for SRC in "${SRCS[@]}"; do
    echo "# Compiling: $SRC"
    # pedantic?
    g++ -std=gnu++17 -Wall -include prem.cpp "$SRC" -o /dev/null \
        || (echo && echo "# Failed while compiling: $SRC" && false)
    echo "# Success."
done

