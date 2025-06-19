#!/bin/bash

# Project compilation
g++ -std=c++11 main.cpp -o main

# Verify compilation result
if [ $? -eq 0 ]; then
    echo "Compilation completed successfully!"
    echo ""
    
    # Run the built program
    ./main
    echo ""
else
    echo "Error in compiling!"
    echo ""
fi
