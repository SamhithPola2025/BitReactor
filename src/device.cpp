#include <cstdint>
#include <iostream>
#include "device_io.hpp"
#include <cassert>

int main() {
    SSDDevice ssd(1, "SSD0", 16, 512);
 
    uint8_t data[512] = {0};
    uint8_t buffer[512] = {0};

    data[0] = 42;
    data[1] = 99;
    ssd.writeBlock(0, data, 512);

    ssd.readBlock(0, buffer, 512);

    std::cout << "Block 0 first 10 bytes:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << static_cast<int>(buffer[i]) << " ";
    }
    std::cout << std::endl;

    for (int block = 0; block < 3; ++block) {
        std::fill(std::begin(data), std::end(data), 0); 
        data[0] = block * 10;
        ssd.writeBlock(block, data, 512);

        std::fill(std::begin(buffer), std::end(buffer), 0); 
        ssd.readBlock(block, buffer, 512);

        std::cout << "Block " << block << " first byte: " << static_cast<int>(buffer[0]) << std::endl;
    }

    std::fill(std::begin(data), std::end(data), 0);

    std::fill(std::begin(buffer), std::end(buffer), 0); 
    ssd.readBlock(20, buffer, 512);

    data[0] = 42;
    data[1] = 99;
    ssd.writeBlock(0, data, 512);

    ssd.readBlock(0, buffer, 512);

    assert(buffer[0] == 42);
    assert(buffer[1] == 99);
    std::cout << "Data integrity test passed!" << std::endl;

    return 0;
}