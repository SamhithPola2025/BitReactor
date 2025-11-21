#include <cstring>
#include <cstdlib>
#include <iostream>
#include "cpu_arch.hpp"
#include "device_io.hpp"

// Function declarations
void writeDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, const uint8_t* data, size_t size);
void readDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, uint8_t* buffer, size_t size);

int CPUInit(
    CPUArchitecture &cpu,
    const char* name,
    uint8_t num_registers,
    uint32_t cache_size,
    uint8_t instruction_set,
    uint8_t word_size,
    uint8_t *registers,
    uint8_t flags,
    uint8_t *memory,
    uint16_t sp,
    uint16_t pc,
    uint16_t bp,
    uint16_t acc
) {
    strncpy(cpu.name, name, sizeof(cpu.name) - 1);
    cpu.name[sizeof(cpu.name) - 1] = '\0';

    cpu.num_devices = 0;
    for (int i = 0; i < 4; i++) cpu.devices[i] = nullptr;

    cpu.num_registers = num_registers;
    cpu.cache_size = cache_size;
    cpu.instruction_set = instruction_set;
    cpu.word_size = word_size;
    cpu.pc = pc;
    cpu.flags = 0;

    cpu.registers = new uint8_t[num_registers];
    if (!cpu.registers) return -1;
    memset(cpu.registers, 0, num_registers * sizeof(uint8_t));

    cpu.memory = new uint16_t[MEMORY_SIZE];
    if (!cpu.memory) {
        delete[] cpu.registers;
        return -1;
    }
    memset(cpu.memory, 0, MEMORY_SIZE * sizeof(uint16_t));

    cpu.sp = sp;
    cpu.bp = bp;
    cpu.acc = acc;

    return 0;
}

void CPUShutdown(CPUArchitecture &cpu) {
    delete[] cpu.registers;
    delete[] cpu.memory;
    cpu.registers = nullptr;
    cpu.memory = nullptr;
}

void LoadProgram(CPUArchitecture &cpu, const uint16_t* program, size_t size) {
    if (size > MEMORY_SIZE) {
        std::cerr << "Program size exceeds memory capacity." << std::endl;
        return;
    }
    memcpy(cpu.memory, program, size * sizeof(uint16_t));
}