#!/bin/bash

# Project compilation
g++ -std=c++11 main.cpp -o main

# Verify compilation result
if [ $? -eq 0 ]; then
    echo "Compilation completed successfully!"
    echo ""
    
    # Run program builded
    ./main
    echo ""
else
    echo ""
    echo "Error in compiling!"
fi
