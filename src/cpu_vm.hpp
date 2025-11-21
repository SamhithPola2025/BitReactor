#pragma once

#include "cpu_arch.hpp"
#include <cstdint>

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
);

void CPUShutdown(CPUArchitecture &cpu);
void LoadProgram(CPUArchitecture &cpu, const uint16_t* program, size_t size);
