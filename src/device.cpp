#include <cstdint>
#include <iostream>
#include "device_io.hpp"

int main() {
    SSDDevice ssd(1, "SSD0", 16, 512);

    //write some data to block 0
    uint8_t data[512] = {0};
    data[0] = 42;
    data[1] = 99;
    ssd.writeBlock(0,data,512);

    uint8_t buffer[512];
    ssd.readBlock(0,buffer,512);

    std::cout << "Block 0 first 10 bytes:" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << static_cast<int>(buffer[i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}