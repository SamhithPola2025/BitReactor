# this is a shell script to compile on linux

echo "Compiling the project..."
g++ -o $OUTPUT_BINARY src/main.cpp src/cpu_vm.cpp src/device_io.cpp src/opcodes.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    # Run the program
    ./$OUTPUT_BINARY
else
    echo "Compilation failed. Please check for errors."
fi