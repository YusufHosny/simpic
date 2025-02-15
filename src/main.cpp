#include "pic10f200.hpp"
#include <iostream>

int main(void) {
    PIC10f200 pic;
    pic.load_program();
    int ix = 0;
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;
    pic.step(); // NOP
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;
    pic.step(); // MOVLW
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;
    pic.step(); // XORLW
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;
    pic.step(); // ANDLW
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;
    pic.step(); // IORLW
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;
    pic.step(); // GOTO 6
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;
    pic.step(); // NOP
    std::cout << ix++ << "-> W: " << pic.getW() << " PC: " << pic.getPC() << " op: " << pic.currentInstruction() << std::endl;

    return 0;
}