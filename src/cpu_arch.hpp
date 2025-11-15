#ifndef CPU_ARCH_HPP
#define CPU_ARCH_HPP

#include <cstdint>

struct CPUArchitecture{
    char name[50];
    uint8_t num_registers;
    uint32_t cache_size; 
    uint8_t instruction_set;
    uint8_t word_size;
    uint8_t *registers;
    // 64 KB = 65,536 bytes (hence the uint16_t) 
    // This is the program counter which holds the memory address of the next instruction to be executed. 
    uint16_t pc; 
    uint8_t flags;
    uint16_t *memory; // this is simulating memory (so you can assume that this is actually detatched)
};


#endif // CPU_ARCH_HPP