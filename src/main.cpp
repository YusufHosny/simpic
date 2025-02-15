#include "pic10f200.hpp"
#include <iostream>

int main(void) {
    PIC10f200 pic;
    pic.setVerbosity(3); // max verbosity

    pic.load_program();
    int ix = 0;
    pic.step(); // NOP
    pic.step(); // MOVLW
    pic.step(); // XORLW
    pic.step(); // ANDLW
    pic.step(); // IORLW
    pic.step(); // GOTO 6
    pic.step(); // NOP

    return 0;
}