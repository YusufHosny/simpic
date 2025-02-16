#pragma once

#include <ranges>
#include <memory>
#include <array>
#include "types.hpp"
#include "instructions.hpp"

enum STATUSBITS {
    GPWUF = 7,
    TO = 4,
    PD = 3,
    Z = 2,
    DC = 1,
    C = 0
};

enum OPTIONBITS {
    GPWU = 7,
    GPPU = 6,
    T0CS = 5,
    T0SE = 4,
    PSA = 3,
    PS2 = 2,
    PS1 = 1,
    PS0 = 0,
};

enum REGISTERS {
    INDF =  0x0,
    TMR0 =  0x1,
    PCL =   0x2,
    STATUS = 0x3,
    FSR = 0x4,
    OSCCAL = 0x5,
    GPIO = 0x6
};

class PIC10f200 {

private:

    std::array<std::unique_ptr<InstructionHandler>, 33> instructions;

    Word programMemory[256];
    Byte DataMemory[16];

    uint8_t verbosity;

    bool PCH;

    Byte W, OPTIONreg, TRISGPIOreg;

    Word instructionRegister;
    Word nextInstructionRegister;

    Word fetch();
    void execute(Word instruction);
    void execute();

public:
    PIC10f200();

    Byte getDMEM(Byte address);
    void setDMEM(Byte address, Byte value);

    Byte getW();
    void setW(Byte value);
    Byte getOption();
    void setOption(Byte value);
    Byte getTris();
    void setTris(Byte value);

    void setTO(bool value);
    void setPD(bool value);
    void setZ(bool value);
    void setDC(bool value);
    void setC(bool value);

    uint16_t getPC();
    void setPC(uint16_t address);

    Byte& INDF();
    Byte& TMR0();
    Byte& PCL();
    Byte& STATUS();
    Byte& FSR();
    Byte& OSCCAL();
    Byte& GPIO();

    void incrememtPC(Byte offset = 1);

    Word currentInstruction();
    Word nextInstruction();
    void setNextInstruction(Word instruction);
    
    void setVerbosity(uint8_t verbosity);

    void reset();
    void step(int cycles = 1);
    void load_program(); // 

};