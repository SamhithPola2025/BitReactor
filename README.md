# BitReactor
BitReactor is an 8-bit CPU architecture simulator designed for experimenting with low-level programming concepts and testing custom instructions. It provides a virtual environment to simulate CPU operations, memory management, and device I/O.

## Coding stats (in hours)!
![coding stats](https://hackatime-badge.hackclub.com/U08AP4Z9S9F/BitReactor)


## Key Features
- **REPL Mode**: Interactively execute instructions in real-time.
- **File Loading**: Load and execute programs from a file like so:
```plaintext
0x010A // ADD 10 to register 0
0x0205 // SUBTRACT 5 from register 0
0x0301 // LOAD value from memory[1] into register 0
0x0402 // STORE value from register 0 into memory[2]
```
- **Customizable Architecture**: Modify registers, memory size, and instruction set.
- **Device I/O Simulation**: Simulate reading and writing to virtual devices like SSDs.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/BitReactor.git
   cd BitReactor
   ```

2. Compile the project:
   ```bash
   g++ -o bitreactor src/main.cpp src/cpu_vm.cpp src/device_io.cpp src/opcodes.cpp
   ```

3. Run the program:
   ```bash
   ./bitreactor
   ```
## You can also just go to releases and run the release in there using ./bitreactor after downloading it, THIS IS ONLY FOR MAC HOWEVER!

## If you are on any other OS:

### Linux
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/BitReactor.git
   cd BitReactor
   ```

2. Use the provided shell script to compile and run the program:
   ```bash
   cd src
   ./build_and_run.sh
   ```

   Alternatively, you can manually compile and run the program:
   ```bash
   cd src
   g++ -o bitreactor src/main.cpp src/cpu_vm.cpp src/device_io.cpp src/opcodes.cpp
   ./bitreactor
   ```

### Windows
1. Clone the repository or download the release archive for Windows from the [Releases](https://github.com/yourusername/BitReactor/releases) page.
2. Extract the archive using a tool like WinRAR, 7-Zip, or the built-in Windows extractor.
3. Use the provided PowerShell script to compile and run the program:
   ```powershell
   cd src
   ./build_and_run.ps1
   ```

   Alternatively, you can manually compile and run the program:
   - Open a Command Prompt or PowerShell in the extracted folder.
   - Compile the program:
     ```powershell
     cd src
     g++ -o bitreactor.exe src/main.cpp src/cpu_vm.cpp src/device_io.cpp src/opcodes.cpp
     ```
   - Run the program:
     ```powershell
     .\bitreactor.exe
     ```

Alternatively, you can double-click the `bitreactor.exe` file in File Explorer to run the program.

## Picture of it working: 
<img width="549" height="305" alt="image" src="https://github.com/user-attachments/assets/90dc483d-cabc-4d7e-a436-fd1975d5d2af" />

## Usage
When you run the program, you will be prompted to choose one of the following options:

1. **REPL Mode**: Interactively execute instructions.
   - Enter instructions in hexadecimal format (e.g., `0x010A`).
   - Type `exit` to quit REPL mode.

2. **Load and Execute the Example Program**:
   - This option runs a predefined program stored in the code.

3. **Load and Execute a Program from a File**:
   - Provide the path to a file containing instructions in hexadecimal format.
   - Example file (`program.txt`):
     ```plaintext
     0x010A // ADD 10 to register 0
     0x0205 // SUBTRACT 5 from register 0
     0x0301 // LOAD value from memory[1] into register 0
     0x0402 // STORE value from register[0] into memory[2]
     ```

4. **Exit**: Quit the program.

## CPU Architecture
The BitReactor CPU is an 8-bit architecture with the following components:
- **Registers**: General-purpose registers for storing intermediate values.
- **Memory**: 64 KB of memory for storing instructions and data.
- **Instruction Set**: Supports basic arithmetic, logical operations, memory access, and device I/O.
- **Program Counter (PC)**: Tracks the current instruction being executed.
- **Stack Pointer (SP)**: Manages the stack for PUSH and POP operations.

### Example Instruction Set
- `0x01XX`: ADD `XX` to register 0.
- `0x02XX`: SUBTRACT `XX` from register 0.
- `0x03XX`: LOAD value from memory[XX] into register 0.
- `0x04XX`: STORE value from register 0 into memory[XX].
- `0x09XX`: READ from device slot `XX`.
- `0x0AXX`: WRITE to device slot `XX`.

## Contributing
Contributions are welcome! If you'd like to improve the project, follow these steps:
1. Fork the repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Make your changes and commit them:
   ```bash
   git commit -m "Add your commit message"
   ```
4. Push to your branch:
   ```bash
   git push origin feature/your-feature-name
   ```
5. Open a pull request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
