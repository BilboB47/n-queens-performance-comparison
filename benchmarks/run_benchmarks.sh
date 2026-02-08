#!/bin/bash

# --- Configuration ---
START_N=4
END_N=17
OUTPUT="nqueens_results.csv"
SOLVERS=("queens_naive" "queens_bitmask" "queens_cuda")

# Ścieżka do build jest o jeden folder wyżej (../build)
BUILD_DIR="../build"

# Write CSV Header
echo "solver,n,solutions,time_seconds" > $OUTPUT

echo "Starting N-Queens Benchmark..."

for ((n=START_N; n<=END_N; n++))
do
    for solver in "${SOLVERS[@]}"
    do
        BINARY="$BUILD_DIR/$solver"
        
        if [ -f "$BINARY" ]; then
            echo "Testing $solver for N=$n"
            # Uruchamiamy i parsujemy wynik
            RESULT=$($BINARY $n)
            echo "$solver,$RESULT" >> $OUTPUT
        else
            echo "Warning: $BINARY not found! Compile your code first."
        fi
    done
done

echo "Done! Data saved in benchmarks/$OUTPUT"