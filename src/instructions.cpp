#include "instructions.hpp"
#include "pic10f200.hpp"

InstructionMatcher::InstructionMatcher(std::string matchOn) : matchOn(matchOn) {};
bool InstructionMatcher::match(const Word input) const {
    for(size_t i = 0; i < 12; i++) {
        if( (matchOn[i] == '1' && !input[11-i]) || (matchOn[i] == '0' && input[11-i]) ) return false;
    }
    return true;
}

InstructionHandler::InstructionHandler(InstructionMatcher matcher, std::string mnemonic) : matcher(matcher), mnemonic(mnemonic) {};
bool InstructionHandler::match(Word input) const {
    return this->matcher.match(input);
}


ADDWF::ADDWF() : InstructionHandler(InstructionMatcher("000111dfffff"), "ADDWF") {};
void ADDWF::execute(PIC10f200 *mcu) {}

ANDWF::ANDWF() : InstructionHandler(InstructionMatcher("000101dfffff"), "ANDWF") {};
void ANDWF::execute(PIC10f200 *mcu) {}

CLRF::CLRF() : InstructionHandler(InstructionMatcher("0000011fffff"), "CLRF") {};
void CLRF::execute(PIC10f200 *mcu) {}

CLRW::CLRW() : InstructionHandler(InstructionMatcher("000001000000"), "CLRW") {};
void CLRW::execute(PIC10f200 *mcu) {}

COMF::COMF() : InstructionHandler(InstructionMatcher("001001dfffff"), "COMF") {};
void COMF::execute(PIC10f200 *mcu) {}

DECF::DECF() : InstructionHandler(InstructionMatcher("000011dfffff"), "DECF") {};
void DECF::execute(PIC10f200 *mcu) {}

DECFSZ::DECFSZ() : InstructionHandler(InstructionMatcher("001011dfffff"), "DECFSZ") {};
void DECFSZ::execute(PIC10f200 *mcu) {}

INCF::INCF() : InstructionHandler(InstructionMatcher("001010dfffff"), "INCF") {};
void INCF::execute(PIC10f200 *mcu) {}

INCFSZ::INCFSZ() : InstructionHandler(InstructionMatcher("001111dfffff"), "INCFSZ") {};
void INCFSZ::execute(PIC10f200 *mcu) {}

IORWF::IORWF() : InstructionHandler(InstructionMatcher("000100dfffff"), "IORWF") {};
void IORWF::execute(PIC10f200 *mcu) {}

MOVF::MOVF() : InstructionHandler(InstructionMatcher("001000dfffff"), "MOVF") {};
void MOVF::execute(PIC10f200 *mcu) {}

MOVWF::MOVWF() : InstructionHandler(InstructionMatcher("0000001fffff"), "MOVWF") {};
void MOVWF::execute(PIC10f200 *mcu) {}

NOP::NOP() : InstructionHandler(InstructionMatcher("000000000000"), "NOP") {};
void NOP::execute(PIC10f200 *mcu) {}

RLF::RLF() : InstructionHandler(InstructionMatcher("001101dfffff"), "RLF") {};
void RLF::execute(PIC10f200 *mcu) {}

RRF::RRF() : InstructionHandler(InstructionMatcher("001100dfffff"), "RRF") {};
void RRF::execute(PIC10f200 *mcu) {}

SUBWF::SUBWF() : InstructionHandler(InstructionMatcher("000010dfffff"), "SUBWF") {};
void SUBWF::execute(PIC10f200 *mcu) {}

SWAPF::SWAPF() : InstructionHandler(InstructionMatcher("001110dfffff"), "SWAPF") {};
void SWAPF::execute(PIC10f200 *mcu) {}

XORWF::XORWF() : InstructionHandler(InstructionMatcher("000110dfffff"), "XORWF") {};
void XORWF::execute(PIC10f200 *mcu) {}

BCF::BCF() : InstructionHandler(InstructionMatcher("0100bbbfffff"), "BCF") {};
void BCF::execute(PIC10f200 *mcu) {}

BSF::BSF() : InstructionHandler(InstructionMatcher("0101bbbfffff"), "BSF") {};
void BSF::execute(PIC10f200 *mcu) {}

BTFSC::BTFSC() : InstructionHandler(InstructionMatcher("0110bbbfffff"), "BTFSC") {};
void BTFSC::execute(PIC10f200 *mcu) {}

BTFSS::BTFSS() : InstructionHandler(InstructionMatcher("0111bbbfffff"), "BTFSS") {};
void BTFSS::execute(PIC10f200 *mcu) {}

ANDLW::ANDLW() : InstructionHandler(InstructionMatcher("1110kkkkkkkk"), "ANDLW") {};
void ANDLW::execute(PIC10f200 *mcu) {
    mcu->setW( mcu->getW() & (mcu->currentInstruction().get() & 0xFF) );
}

CALL::CALL() : InstructionHandler(InstructionMatcher("1001kkkkkkkk"), "CALL") {};
void CALL::execute(PIC10f200 *mcu) {}

CLRWDT::CLRWDT() : InstructionHandler(InstructionMatcher("000000000100"), "CLRWDT") {};
void CLRWDT::execute(PIC10f200 *mcu) {}

GOTO::GOTO() : InstructionHandler(InstructionMatcher("101kkkkkkkkk"), "GOTO") {};
void GOTO::execute(PIC10f200 *mcu) {
    mcu->setPC( mcu->currentInstruction().get() & 0x1FF );
}

IORLW::IORLW() : InstructionHandler(InstructionMatcher("1101kkkkkkkk"), "IORLW") {};
void IORLW::execute(PIC10f200 *mcu) {
    mcu->setW( mcu->getW() | (mcu->currentInstruction().get() & 0xFF) );
}

MOVLW::MOVLW() : InstructionHandler(InstructionMatcher("1100kkkkkkkk"), "MOVLW") {};
void MOVLW::execute(PIC10f200 *mcu) {
    mcu->setW(mcu->currentInstruction().get() & 0xFF);
}

OPTION::OPTION() : InstructionHandler(InstructionMatcher("000000000010"), "OPTION") {};
void OPTION::execute(PIC10f200 *mcu) {}

RETLW::RETLW() : InstructionHandler(InstructionMatcher("1000kkkkkkkk"), "RETLW") {};
void RETLW::execute(PIC10f200 *mcu) {}

SLEEP::SLEEP() : InstructionHandler(InstructionMatcher("000000000011"), "SLEEP") {};
void SLEEP::execute(PIC10f200 *mcu) {}

TRIS::TRIS() : InstructionHandler(InstructionMatcher("000000000fff"), "TRIS") {};
void TRIS::execute(PIC10f200 *mcu) {}

XORLW::XORLW() : InstructionHandler(InstructionMatcher("1111kkkkkkkk"), "XORLW") {};
void XORLW::execute(PIC10f200 *mcu) {
    mcu->setW( mcu->getW() ^ (mcu->currentInstruction().get() & 0xFF) );
}

