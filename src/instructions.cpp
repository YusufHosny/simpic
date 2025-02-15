#include "instructions.hpp"
#include "pic10f200.hpp"

InstructionMatcher::InstructionMatcher(std::string matchOn) : matchOn(matchOn) {};
bool InstructionMatcher::match(const Word input) const {
    for(size_t i = 0; i < 12; i++) {
        if( (matchOn[i] == '1' && !input[11-i]) || (matchOn[i] == '0' && input[11-i]) ) return false;
    }
    return true;
}

InstructionHandler::InstructionHandler(InstructionMatcher matcher) : matcher(matcher) {};
bool InstructionHandler::match(Word input) const {
    return this->matcher.match(input);
}

NOP::NOP() : InstructionHandler(InstructionMatcher("000000000000")) {};
void NOP::execute(PIC10f200 *mcu) {}

MOVLW::MOVLW() : InstructionHandler(InstructionMatcher("1100kkkkkkkk")) {};
void MOVLW::execute(PIC10f200 *mcu) {
    mcu->setW(mcu->currentInstruction().get() & 0xFF);
}

ANDLW::ANDLW() : InstructionHandler(InstructionMatcher("1110kkkkkkkk")) {};
void ANDLW::execute(PIC10f200 *mcu) {
    mcu->setW( mcu->getW() & (mcu->currentInstruction().get() & 0xFF) );
}

IORLW::IORLW() : InstructionHandler(InstructionMatcher("1101kkkkkkkk")) {};
void IORLW::execute(PIC10f200 *mcu) {
    mcu->setW( mcu->getW() | (mcu->currentInstruction().get() & 0xFF) );
}

XORLW::XORLW() : InstructionHandler(InstructionMatcher("1111kkkkkkkk")) {};
void XORLW::execute(PIC10f200 *mcu) {
    mcu->setW( mcu->getW() ^ (mcu->currentInstruction().get() & 0xFF) );
}

GOTO::GOTO() : InstructionHandler(InstructionMatcher("101kkkkkkkkk")) {};
void GOTO::execute(PIC10f200 *mcu) {
    mcu->setPC( mcu->currentInstruction().get() & 0x1FF );
}