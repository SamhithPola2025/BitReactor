#include <cstring>
#include <cstdlib>
#include "cpu_arch.hpp"
#include <iostream>
#include "device_io.hpp"

uint16_t program[] = {
    0x010A,
    0x0205,
    0x040A,
    0x030A,
    0x0502,
};

int CPUInit(
        CPUArchitecture &cpu,
        const char* name,
        uint8_t num_registers,
        uint32_t cache_size,
        uint8_t instruction_set,
        uint8_t word_size,
        uint8_t *registers,
        uint8_t flags,
        uint8_t *memory, // this is simulating memory (so you can assume that this is actually detatched)
        uint16_t sp, // stack pointer
        uint16_t pc, // program counter (holds the memory address for the next instruction that will be executed)
        uint16_t bp, // base pointer
        uint16_t acc // accumulator
) {
    strncpy(cpu.name, name, sizeof(cpu.name) - 1);
    cpu.name[sizeof(cpu.name) - 1] = '\0';

    cpu.num_devices = 0;
    for(int i=0; i<4; i++) cpu.devices[i] = nullptr;

    cpu.num_registers = num_registers;
    cpu.cache_size = cache_size;
    cpu.instruction_set = instruction_set;
    cpu.word_size = word_size;
    cpu.pc = pc;
    cpu.flags = 0;

    cpu.registers = new uint8_t[num_registers];
    if (!cpu.registers) return -1;
    memset(cpu.registers, 0, num_registers * sizeof(uint8_t));

    cpu.memory = new uint16_t[64 * 1024];
    if (!cpu.memory) {
        delete[] cpu.registers;
        return -1;
    }
    memset(cpu.memory, 0, 64 * 1024 * sizeof(uint16_t));

    cpu.sp = sp;

    return 0;
}

void CPUShutdown(CPUArchitecture &cpu) {
    delete[] cpu.registers;
    delete[] cpu.memory;
    cpu.registers = nullptr;
    cpu.memory = nullptr;
}

void LoadProgram(CPUArchitecture &cpu, const uint16_t* program, size_t size) {
    if (size > 64 * 1024) {
        return;
    }
    memcpy(cpu.memory, program, size * sizeof(uint16_t));
}

void FetchDecodeExecute(CPUArchitecture &cpu) {
    uint16_t instruction = cpu.memory[cpu.pc]; //fetch the instruction thats at program counter

    uint8_t opcode = (instruction >> 8) & 0xFF; //operation code
    uint8_t operand = instruction & 0xFF; // operand

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
        default:
            std::cerr << "UNKNOWN OPCODE: " << (int)opcode << std::endl;
            break;
    }
    cpu.pc++;
}

void writeDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, const uint8_t* data, size_t size) {
    if(slot >= cpu.num_devices || cpu.devices[slot] == nullptr) return;
    cpu.devices[slot]->writeBlock(block, data, size);
}

void readDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, uint8_t* buffer, size_t size) {
    if(slot >= cpu.num_devices || cpu.devices[slot] == nullptr) return;
    cpu.devices[slot]->readBlock(block, buffer, size);
}

int main() {
    CPUArchitecture cpu;
    SSDDevice* ssd0 = new SSDDevice(0, "SSD0", 16, 512);
    cpu.devices[0] = ssd0;
    cpu.num_devices = 1;

    uint8_t* registers = nullptr;
    uint8_t* memory = nullptr;

    if (CPUInit(cpu, "MyCPU", 8, 64*1024, 1, 8, registers, 0, memory, (64*1024)-1, 0, 0, 0) != 0) {
        std::cerr << "Failed to initialize CPU" << std::endl;
        return -1;
    }

    LoadProgram(cpu, program, sizeof(program) / sizeof(program[0]));

    while (cpu.pc < sizeof(program) / sizeof(program[0])) {
        FetchDecodeExecute(cpu);
    }

    CPUShutdown(cpu);
    return 0;
}
