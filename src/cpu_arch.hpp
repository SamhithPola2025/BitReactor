#pragma once

#include <cstdint>
#include "device_io.hpp"

struct CPUArchitecture{
    Device* devices[4];
    uint8_t num_devices;
    char name[50];
    uint8_t num_registers;
    uint32_t cache_size; 
    uint8_t instruction_set;
    uint8_t word_size;
    uint8_t *registers;
    // 64 KB = 65,536 bytes (hence the uint16_t) 
    // This is the program counter which holds the memory address of the next instruction to be executed. 

    uint8_t flags;
    uint16_t *memory; // this is simulating memory (so you can assume that this is actually detatched)

    //special registers
    uint16_t sp; // stack pointer
    uint16_t pc; // program counter (holds the memory address for the next instruction that will be executed)
    uint16_t bp; // base pointer
    uint16_t acc; // accumulator
};