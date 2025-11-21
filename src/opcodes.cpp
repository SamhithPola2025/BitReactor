#include <iostream>
#include <cstdint>
#include "cpu_arch.hpp"
#include "device_io.hpp"
#include "opcodes.hpp"

void FetchDecodeExecute(CPUArchitecture &cpu) {
    uint16_t instruction = cpu.memory[cpu.pc]; //fetch the instruction thats at program counter
    constexpr size_t MEMORY_SIZE = 64 * 1024; // define memory size globally

    uint8_t opcode = (instruction >> 8) & 0xFF; //operation code
    uint16_t operand = instruction & 0xFF;

    if (operand >= MEMORY_SIZE) {
        std::cerr << "ERROR: Memory access out of bounds." << std::endl;
        return;
    } else {
        switch (opcode) {
            case 0x01:
                cpu.registers[0] += operand;
                std::cout << "ADD OPERATION" << std::endl;
                break;
            case 0x02:
                cpu.registers[0] -= operand;
                std::cout << "SUBTRACT OPERATION" << std::endl;
                break;
            case 0x03:
                cpu.registers[0] = cpu.memory[operand];
                std::cout << "LOAD" << std::endl;
                break;
            case 0x04:
                cpu.memory[operand] = cpu.registers[0];
                std::cout << "STORE" << std::endl;
                break;
            case 0x05:
                cpu.memory[0] *= operand;
                std::cout << "MULTIPLY OPERATION" << std::endl;
                break;
            case 0x06: 
                std::cout << "DIVIDE OPERATION" << std::endl;
                if (operand != 0) { // prevents the division by 0 issue
                    cpu.registers[0] /= operand;
                } else {
                    std::cerr << "ERROR: DIVISION BY 0" << std::endl;
                }
                break;
            case 0x07: // PUSH
                cpu.memory[cpu.sp--] = cpu.registers[0];
                std::cout << "PUSH OPERATION" << std::endl;
                break;
            case 0x08: // POP
                cpu.registers[0] = cpu.memory[++cpu.sp];
                std::cout << "POP OPERATION" << std::endl;
                break;
            case 0x09: {
                uint8_t slot = operand;
                uint16_t block = cpu.registers[1];
                uint8_t* buffer = reinterpret_cast<uint8_t*>(&cpu.memory[cpu.registers[2]]);
                size_t size = cpu.registers[3];
                readDevice(cpu, slot, block, buffer, size);
                std::cout << "READ FROM SSD DEVICE" << std::endl;
                break;
            } 
            case 0x0A: { // write to SSD
                uint8_t slot = operand; 
                uint16_t block = cpu.registers[1]; 
                uint8_t* data = reinterpret_cast<uint8_t*>(&cpu.memory[cpu.registers[2]]); 
                size_t size = cpu.registers[3];
                writeDevice(cpu, slot, block, data, size);
                std::cout << "WRITE TO SSD DEVICE" << std::endl;
                break;
            }
            case 0x0B: // AND
                cpu.registers[0] &= operand;
                std::cout << "AND OPERATION" << std::endl;
                break;
            case 0x0C: //OR
                cpu.registers[0] |= operand;
                std::cout << "OR OPERATION" << std::endl;
                break;
            default:
                std::cerr << "UNKNOWN OPCODE: " << (int)opcode << std::endl;
                break;
        }
        cpu.pc++;
    }
}