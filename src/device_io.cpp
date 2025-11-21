#include "device_io.hpp"
#include <iostream>
#include <cstdint>
#include "cpu_arch.hpp"

void writeDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, const uint8_t* data, size_t size) {
    if (slot >= cpu.num_devices || cpu.devices[slot] == nullptr) {
        std::cerr << "Invalid device slot: " << (int)slot << std::endl;
        return;
    }
}

void readDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, uint8_t* buffer, size_t size) {
    if (slot >= cpu.num_devices || cpu.devices[slot] == nullptr) {
        std::cerr << "Invalid device slot: " << (int)slot << std::endl;
        return;
    }
    cpu.devices[slot]->readBlock(block, buffer, size);
}