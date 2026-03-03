#!/bin/bash

# Fixed n value
n=1000

encoders=(--reduced --seq --BDD --product --card --duplex --scl)

# w runs from 1 to 1000
w_values=$(seq 2 1 1000)

# Timeout (600 seconds per command)
timeout_duration=600

# Memory limit (30000MB = 30000 * 1024 KB)
memory_limit=$((30000 * 1024))

for w in $w_values; do
    for encoder in "${encoders[@]}"; do
        w_plus_1=$((w + 1))

        ulimit -v $memory_limit

        echo "Running: timeout $timeout_duration ./ladder_amo_enc $n $encoder -set-lb $w -set-ub $w_plus_1"
        timeout $timeout_duration ./ladder_amo_enc $n $encoder -set-lb $w -set-ub $w_plus_1

        exit_code=$?
        if [ $exit_code -eq 124 ]; then
            echo "Command timed out after $timeout_duration seconds"
        elif [ $exit_code -eq 137 ]; then
            echo "Command was killed due to exceeding memory limit ($memory_limit KB)"
        fi
    done
done
