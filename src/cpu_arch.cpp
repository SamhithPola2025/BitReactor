#include <cstring>
#include <cstdlib>
#include "cpu_arch.hpp"

int main() {
    
    return 0;
}

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
        uint16_t pc
) {
    strncpy(cpu.name, name, sizeof(cpu.name) - 1);
    cpu.name[sizeof(cpu.name) - 1] = '\0';

    cpu.num_registers = num_registers;
    cpu.cache_size = cache_size;
    cpu.instruction_set = instruction_set;
    cpu.word_size = word_size;
    cpu.pc = pc;
    cpu.flags = flags = 0;

    cpu.registers = new uint8_t[num_registers];
    if (cpu.registers == nullptr) {
        return -1; // returning an error if allocation happens to fail
    }
    memset(cpu.registers, 0, num_registers * sizeof(uint16_t));

    cpu.memory = new uint16_t[64 * 1024];
    if (cpu.memory == nullptr) {
        delete[] cpu.registers;
        return -1;
    }
    memset(cpu.memory, 0, 64 * 1024 * sizeof(uint16_t));

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