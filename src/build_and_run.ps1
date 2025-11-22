# This is a PowerShell script to compile and run the project on Windows

# Set the output binary name
$outputBinary = "bitreactor.exe"

# Compile the project
Write-Host "Compiling the project..."
g++ -o $outputBinary src/main.cpp src/cpu_vm.cpp src/device_io.cpp src/opcodes.cpp

# Check if compilation was successful
if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilation successful. Running the program..."
    # Run the program
    Start-Process -NoNewWindow -Wait -FilePath ".\$outputBinary"
} else {
    Write-Host "Compilation failed. Please check for errors."
}