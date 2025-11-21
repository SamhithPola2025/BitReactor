#pragma once

#include <cstdint>
#include <vector>
#include "cpu_arch.hpp"

struct CPUArchitecture;

class Device {
public:
    uint16_t id; // identifier
    const char* name;

    Device(uint16_t dev_id, const char* dev_name) : id(dev_id), name(dev_name) {}
    virtual ~Device() = default;

    virtual void writeBlock(uint16_t block, const uint8_t* data, size_t size) = 0;
    virtual void readBlock(uint16_t block, uint8_t* buffer, size_t size) = 0;    
};

// example SSD Device
class SSDDevice : public Device {
public:
    uint16_t numBlocks;
    uint16_t blockSize;
    std::vector<uint8_t> storage;

    SSDDevice(uint16_t dev_id, const char* dev_name, uint16_t blocks, uint16_t blkSize)
        : Device(dev_id, dev_name), numBlocks(blocks), blockSize(blkSize) {
        storage.resize(numBlocks * blockSize, 0);
    }

    void writeBlock(uint16_t block, const uint8_t* data, size_t size) override {
        if (block >= numBlocks || size > blockSize) return;
        std::memcpy(&storage[block * blockSize], data, size);
    }

    void readBlock(uint16_t block, uint8_t* buffer, size_t size) override {
        if (block >= numBlocks || size > blockSize) return;
        std::memcpy(buffer, &storage[block * blockSize], size);
    }
    
};

void writeDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, const uint8_t* data, size_t size);
void readDevice(CPUArchitecture &cpu, uint8_t slot, uint16_t block, uint8_t* buffer, size_t size);