#include "pic10f200.hpp"

PIC10f200::PIC10f200() : PCH(false) {
    this->instructions = {
        std::make_unique<NOP>(),
        std::make_unique<MOVLW>(),
        std::make_unique<ANDLW>(),
        std::make_unique<XORLW>(),
        std::make_unique<IORLW>(),
        std::make_unique<GOTO>()
    };
}

Byte PIC10f200::getDMEM(Byte address) { return this->DataMemory[address.get()]; }
void PIC10f200::setDMEM(Byte address, Byte value) { this->DataMemory[address.get()] = value; }

Byte PIC10f200::getW() { return this->W; }
void PIC10f200::setW(Byte value) { this->W = value; }

uint16_t PIC10f200::getPC() { return ((this->PCH & 0b1) << 8) + this->PCL().get(); }
void PIC10f200::setPC(uint16_t value) {
    if(value > 0x1FF) throw std::out_of_range("address out of memory space");
    this->PCL() = value & 0xFF;
    this->PCH = (value & 0x100) >> 8;
}

Word PIC10f200::currentInstruction() { return this->instructionRegister; }

Byte& PIC10f200::INDF() { return this->DataMemory[this->DataMemory[REGISTERS::FSR].get()]; }
Byte& PIC10f200::TMR0() { return this->DataMemory[REGISTERS::TMR0]; }
Byte& PIC10f200::PCL() { return this->DataMemory[REGISTERS::PCL]; }
Byte& PIC10f200::STATUS() { return this->DataMemory[REGISTERS::STATUS]; }
Byte& PIC10f200::FSR() { return this->DataMemory[REGISTERS::FSR]; }
Byte& PIC10f200::OSCCAL() { return this->DataMemory[REGISTERS::OSCCAL]; }
Byte& PIC10f200::GPIO() { return this->DataMemory[REGISTERS::GPIO]; }

void PIC10f200::incrememtPC(Byte offset) {
    Byte PCL = this->getDMEM(REGISTERS::PCL);
    this->setDMEM(REGISTERS::PCL, PCL + offset);

    if(PCL.get() + offset.get() > 0xFF) PCH ^= 0b1;
}

void PIC10f200::reset() {
    this->PCH = 0;
    this->PCL() = 0;
}

void PIC10f200::step() {
    this->execute(this->fetch());
}

void PIC10f200::execute(Word instruction) {
    for(auto& handler : instructions) {
        if(handler->match(instruction)) {
            handler->execute(this);
            return;
        }
    }
    throw std::invalid_argument("Unknown Instruction");
}

Word PIC10f200::fetch() {
    this->instructionRegister = this->programMemory[this->getPC()];
    this->incrememtPC();
    return instructionRegister;
}

void PIC10f200::load_program() { // todo arbitrary program, currently test
    this->programMemory[0] = Word(0b000000000000); // NOP
    this->programMemory[1] = Word(0b110011110101); // MOVLW 0xF5
    this->programMemory[2] = Word(0b111111111111); // XORLW 0xFF (W -> 0x0A)
    this->programMemory[3] = Word(0b111000000000); // ANDLW 0x00 (W -> 0x00)
    this->programMemory[4] = Word(0b110111111111); // IORLW 0xFF (W -> 0xFF)
    this->programMemory[5] = Word(0b101000000000); // GOTO 0
}