#!/bin/bash

# Project compilation
g++ -std=c++11 -g main.cpp ./classes/node.cpp ./classes/min_priority_queue.cpp -o main

# Verify compilation result
if [ $? -eq 0 ]; then
    echo "Compilation completed successfully!"
    echo ""
    
    # Run program builded
    ./main
else
    echo ""
    echo "Error in compiling!"
fi
