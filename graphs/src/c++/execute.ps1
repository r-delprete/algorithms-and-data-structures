# Project compilation
g++ -std=c++11 -g main.cpp -o main.exe

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
