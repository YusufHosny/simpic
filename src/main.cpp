#include "pic10f200.hpp"
#include <iostream>

int main(void) {
    PIC10f200 pic;
    pic.setVerbosity(3); // max verbosity

    pic.load_program();
    int ix = 0;
    pic.step(10); 

    return 0;
}