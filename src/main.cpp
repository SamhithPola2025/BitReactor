#include <iostream>
#include <fstream>
#include <memory>
#include "cpu_arch.hpp"
#include "device_io.hpp"
#include "cpu_vm.hpp"
#include "opcodes.hpp"

constexpr int MENU_REPL = 1;
constexpr int MENU_EXAMPLE_PROGRAM = 2;
constexpr int MENU_LOAD_FROM_FILE = 3;
constexpr int MENU_EXIT = 4;

uint16_t program[] = {
    0x010A, // ADD 10 to register 0
    0x0205, // SUBTRACT 5 from register 0
    0x0301, // LOAD value from memory[1] into register 0
    0x0402, // STORE value from register 0 into memory[2]
    0x0502, // MULTIPLY memory[0] by 2
    0x0602, // DIVIDE register 0 by 2
    0x0700, // PUSH register 0 onto the stack
    0x0800, // POP value from the stack into register 0
    0x0900, // READ from SSD device in slot 0
    0x0A00  // WRITE to SSD device in slot 0
};

void RunREPL(CPUArchitecture &cpu) {
    std::cout << "Entering REPL mode. Type instructions in hexadecimal (e.g., 0x010A). Type 'exit' to quit.\n";
    while (true) {
        std::cout << "> ";
        std::string input;
        std::cin >> input;

        if (input == "exit") {
            break;
        }

        try {
            uint16_t instruction = std::stoi(input, nullptr, 16);
            cpu.memory[cpu.pc++] = instruction;
            FetchDecodeExecute(cpu);
        } catch (...) {
            std::cerr << "Invalid instruction. Please enter a valid hexadecimal value.\n";
        }
    }
}

void LoadAndExecuteFromFile(CPUArchitecture &cpu) {
    std::cout << "Enter the filename: ";
    std::string filename;
    std::cin >> filename;

    std::vector<uint16_t> instructions = loadProgramFromFile(filename);
    if (instructions.empty()) {
        std::cerr << "Failed to load program from file.\n";
        return;
    }

    std::cout << "Loading and executing program from file...\n";
    LoadProgram(cpu, instructions.data(), instructions.size());
    while (cpu.pc < instructions.size()) {
        FetchDecodeExecute(cpu);
    }
}

std::vector<uint16_t> loadProgramFromFile(const std::string& filename) {
    std::vector<uint16_t> instructions;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return instructions;
    }

    uint16_t instruction;
    while (file >> std::hex >> instruction) { // Read instructions in hexadecimal format
        instructions.push_back(instruction);
    }

    file.close();
    return instructions;
}

int main() {
    CPUArchitecture cpu;
    std::unique_ptr<SSDDevice> ssd0 = std::make_unique<SSDDevice>(0, "SSD0", 16, 512);
    cpu.devices[0] = ssd0.get();
    cpu.num_devices = 1;

    if (CPUInit(cpu, "MyCPU", 8, 64 * 1024, 1, 8, nullptr, 0, nullptr, (64 * 1024) - 1, 0, 0, 0) != 0) {
        std::cerr << "Failed to initialize CPU" << std::endl;
        return -1;
    }

    while (true) {
        std::cout << "\nChoose an option:\n";
        std::cout << "1. REPL (Interactive Mode)\n";
        std::cout << "2. Load and execute the example program\n";
        std::cout << "3. Load and execute a program from a file\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == MENU_EXIT) {
            break;
        }

        switch (choice) {
            case MENU_REPL:
                RunREPL(cpu);
                break;
            case MENU_EXAMPLE_PROGRAM:
                std::cout << "Loading and executing the example program...\n";
                LoadProgram(cpu, program, sizeof(program) / sizeof(program[0]));
                while (cpu.pc < sizeof(program) / sizeof(program[0])) {
                    FetchDecodeExecute(cpu);
                }
                break;
            case MENU_LOAD_FROM_FILE:
                LoadAndExecuteFromFile(cpu);
                break;
            default:
                std::cerr << "Invalid choice. Please try again.\n";
                break;
        }
    }

    CPUShutdown(cpu);
    return 0;
}

