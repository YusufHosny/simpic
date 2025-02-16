#include "pic10f200.hpp"

PIC10f200::PIC10f200() : PCH(false), verbosity(0) {
    this->instructions = {
        std::make_unique<ADDWF>(),
        std::make_unique<ANDWF>(),
        std::make_unique<CLRF>(),
        std::make_unique<CLRW>(),
        std::make_unique<COMF>(),
        std::make_unique<DECF>(),
        std::make_unique<DECFSZ>(),
        std::make_unique<INCF>(),
        std::make_unique<INCFSZ>(),
        std::make_unique<IORWF>(),
        std::make_unique<MOVF>(),
        std::make_unique<MOVWF>(),
        std::make_unique<NOP>(),
        std::make_unique<RLF>(),
        std::make_unique<RRF>(),
        std::make_unique<SUBWF>(),
        std::make_unique<SWAPF>(),
        std::make_unique<XORWF>(),

        std::make_unique<BCF>(),
        std::make_unique<BSF>(),
        std::make_unique<BTFSC>(),
        std::make_unique<BTFSS>(),

        std::make_unique<ANDLW>(),
        std::make_unique<CALL>(),
        std::make_unique<GOTO>(),
        std::make_unique<IORLW>(),
        std::make_unique<MOVLW>(),
        std::make_unique<OPTION>(),
        std::make_unique<RETLW>(),
        std::make_unique<SLEEP>(),
        std::make_unique<TRIS>(),
        std::make_unique<XORLW>()
    };
}

Byte PIC10f200::getDMEM(Byte address) { return this->DataMemory[address.get()]; }
void PIC10f200::setDMEM(Byte address, Byte value) { 
    this->DataMemory[address.get()] = value;
    if(verbosity > 1) std::cout << "DMEM[" << address << "] = " << value << std::endl;
}

Byte PIC10f200::getW() { return this->W; }
void PIC10f200::setW(Byte value) { 
    this->W = value; 
    if(verbosity > 1) std::cout << "W = " << this->W << std::endl;
}

Byte PIC10f200::getOption() { return this->OPTIONreg; }
void PIC10f200::setOption(Byte value) {
    this->OPTIONreg = value; 
    if(verbosity > 1) std::cout << "OPTION = " << this->OPTIONreg << std::endl;
}

Byte PIC10f200::getTris() { return this->TRISGPIOreg; }
void PIC10f200::setTris(Byte value) {
    this->TRISGPIOreg = value; 
    if(verbosity > 1) std::cout << "TRIS = " << this->TRISGPIOreg << std::endl;
}

uint16_t PIC10f200::getPC() { return ((this->PCH & 0b1) << 8) + this->PCL().get(); }
void PIC10f200::setPC(uint16_t value) {
    if(value > 0x1FF) throw std::out_of_range("address out of memory space");
    this->PCL() = value & 0xFF;
    this->PCH = (value & 0x100) >> 8;

    if(verbosity > 1) std::cout << "PC = " << this->getPC() << std::endl;
}

Word PIC10f200::currentInstruction() { return this->instructionRegister; }
Word PIC10f200::nextInstruction() { return this->nextInstructionRegister; }
void PIC10f200::setNextInstruction(Word instruction) { this->nextInstructionRegister = instruction; }


void PIC10f200::setVerbosity(uint8_t verbosity) { this->verbosity = verbosity; }

void PIC10f200::setTO(bool value) { 
    Byte byte = this->getDMEM(REGISTERS::STATUS);
    byte.setBit(STATUSBITS::TO, value);
    this->setDMEM(REGISTERS::STATUS, byte);
}

void PIC10f200::setPD(bool value){ 
    Byte byte = this->getDMEM(REGISTERS::STATUS);
    byte.setBit(STATUSBITS::PD, value);
    this->setDMEM(REGISTERS::STATUS, byte);
}

void PIC10f200::setZ(bool value) { 
    Byte byte = this->getDMEM(REGISTERS::STATUS);
    byte.setBit(STATUSBITS::Z, value);
    this->setDMEM(REGISTERS::STATUS, byte);
}

void PIC10f200::setDC(bool value){ 
    Byte byte = this->getDMEM(REGISTERS::STATUS);
    byte.setBit(STATUSBITS::DC, value);
    this->setDMEM(REGISTERS::STATUS, byte);
}

void PIC10f200::setC(bool value) { 
    Byte byte = this->getDMEM(REGISTERS::STATUS);
    byte.setBit(STATUSBITS::C, value);
    this->setDMEM(REGISTERS::STATUS, byte);
}


Byte& PIC10f200::INDF() { return this->DataMemory[this->DataMemory[REGISTERS::FSR].get()]; }
Byte& PIC10f200::TMR0() { return this->DataMemory[REGISTERS::TMR0]; }
Byte& PIC10f200::PCL() { return this->DataMemory[REGISTERS::PCL]; }
Byte& PIC10f200::STATUS() { return this->DataMemory[REGISTERS::STATUS]; }
Byte& PIC10f200::FSR() { return this->DataMemory[REGISTERS::FSR]; }
Byte& PIC10f200::OSCCAL() { return this->DataMemory[REGISTERS::OSCCAL]; }
Byte& PIC10f200::GPIO() { return this->DataMemory[REGISTERS::GPIO]; }

void PIC10f200::incrememtPC(Byte offset) {
    this->setPC(this->getPC() + offset.get());
}

void PIC10f200::reset() {
    this->PCH = 1;
    this->PCL() = 0xFF;

    // register reset values
    this->setDMEM(REGISTERS::STATUS, 0b00011000);
    this->setDMEM(REGISTERS::FSR, 0b11100000);
    this->setDMEM(REGISTERS::OSCCAL, 0b11111110);

    this->fetch(); // fetch first instruction

    if(verbosity > 0) std::cout << "PIC10f200 reset." << std::endl;

}

void PIC10f200::step(int cycles) {
    for(int i = 0; i < cycles; i++) {
        this->fetch();
        this->execute();
    }

    if(verbosity > 0) std::cout << "Stepped " << cycles << " cycle(s)." << std::endl;
}

void PIC10f200::execute(Word instruction) {
    for(auto& handler : instructions) {
        if(handler->match(instruction)) {
            if(verbosity > 1) std::cout << "executing: " << handler->mnemonic << " (" << instruction << ")" << std::endl;
            handler->execute(this);
            this->incrememtPC();
            return;
        }
    }
    throw std::invalid_argument("Unknown Instruction");
}

void PIC10f200::execute() {
    this->execute(instructionRegister);
}

Word PIC10f200::fetch() {
    this->instructionRegister = this->nextInstructionRegister;
    this->nextInstructionRegister = this->programMemory[this->getPC()];
    
    return instructionRegister;
}

void PIC10f200::load_program() { // todo arbitrary program, currently test
    this->programMemory[0] = Word(0b000000000000); // NOP
    this->programMemory[1] = Word(0b110011110101); // MOVLW 0xF5
    this->programMemory[2] = Word(0b111111111111); // XORLW 0xFF (W -> 0x0A)
    this->programMemory[3] = Word(0b111000000000); // ANDLW 0x00 (W -> 0x00)
    this->programMemory[4] = Word(0b110111111111); // IORLW 0xFF (W -> 0xFF)
    this->programMemory[5] = Word(0b101000000000); // GOTO 0

    if(verbosity > 0) std::cout << "Program loaded." << std::endl;
}