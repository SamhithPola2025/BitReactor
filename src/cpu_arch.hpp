#pragma once

#include <cstdint>

class Device;
constexpr size_t MEMORY_SIZE = 64 * 1024; // define memory size globally

struct CPUArchitecture {
    Device* devices[4];
    uint8_t num_devices;
    char name[50];
    uint8_t num_registers;
    uint32_t cache_size;
    uint8_t instruction_set;
    uint8_t word_size;
    uint8_t* registers;
    uint8_t flags;
    uint16_t* memory;

    // Special registers
    uint16_t sp; // Stack pointer
    uint16_t pc; // Program counter
    uint16_t bp; // Base pointer
    uint16_t acc; // Accumulator
};

std::vector<uint16_t> loadProgramFromFile(const std::string& filename);