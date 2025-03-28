# Project compilation
g++ main.cpp ./classes/node.cpp ./classes/edge.cpp ./classes/graph.cpp -o main.exe

# Verify compilation result
if ($?) {
    Write-Host "Compilation completed successfully!`n"
    
    # Run program builded
    ./main.exe
    "`n"
}
else {
    Write-Host "Error in compiling!`n"
}
