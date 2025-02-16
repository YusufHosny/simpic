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

Byte InstructionHandler::getf(PIC10f200 *mcu) {
    Byte f = mcu->currentInstruction().get() & 0x1F;
    return f;
}

Word InstructionHandler::getk(PIC10f200 *mcu, uint8_t length) {
    Word k = mcu->currentInstruction().get() & ((1<<length) - 1);
    return k;
}

bool InstructionHandler::getd(PIC10f200 *mcu) {
    bool d = mcu->currentInstruction()[5];
    return d;
}

Byte InstructionHandler::getb(PIC10f200 *mcu) {
    Byte b = mcu->currentInstruction().get() & 0xE0;
    return b;
}


ADDWF::ADDWF() : InstructionHandler(InstructionMatcher("000111dfffff"), "ADDWF") {};
void ADDWF::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW(), f = mcu->getDMEM(this->getf(mcu));

    Byte result = W + f;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
    mcu->setDC(Byte::digitCarries(W, f));
    mcu->setC(Byte::carries(W, f));
}

ANDWF::ANDWF() : InstructionHandler(InstructionMatcher("000101dfffff"), "ANDWF") {};
void ANDWF::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW(), f = mcu->getDMEM(this->getf(mcu));

    Byte result = W & f;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
}

CLRF::CLRF() : InstructionHandler(InstructionMatcher("0000011fffff"), "CLRF") {};
void CLRF::execute(PIC10f200 *mcu) {
    mcu->setDMEM(this->getf(mcu), 0);
    mcu->setZ(true);
}

CLRW::CLRW() : InstructionHandler(InstructionMatcher("000001000000"), "CLRW") {};
void CLRW::execute(PIC10f200 *mcu) {
    mcu->setW(0);
    mcu->setZ(true);
}

COMF::COMF() : InstructionHandler(InstructionMatcher("001001dfffff"), "COMF") {};
void COMF::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW(), f = mcu->getDMEM(this->getf(mcu));

    Byte result = ~f;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
}

DECF::DECF() : InstructionHandler(InstructionMatcher("000011dfffff"), "DECF") {};
void DECF::execute(PIC10f200 *mcu) {
    Byte f = mcu->getDMEM(this->getf(mcu));

    Byte result = f - 1;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
}

DECFSZ::DECFSZ() : InstructionHandler(InstructionMatcher("001011dfffff"), "DECFSZ") {};
void DECFSZ::execute(PIC10f200 *mcu) {
    // TODO
}

INCF::INCF() : InstructionHandler(InstructionMatcher("001010dfffff"), "INCF") {};
void INCF::execute(PIC10f200 *mcu) {
    Byte f = mcu->getDMEM(this->getf(mcu));

    Byte result = f + 1;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
}

INCFSZ::INCFSZ() : InstructionHandler(InstructionMatcher("001111dfffff"), "INCFSZ") {};
void INCFSZ::execute(PIC10f200 *mcu) {
    // TODO
}

IORWF::IORWF() : InstructionHandler(InstructionMatcher("000100dfffff"), "IORWF") {};
void IORWF::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW(), f = mcu->getDMEM(this->getf(mcu));

    Byte result = W | f;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
}

MOVF::MOVF() : InstructionHandler(InstructionMatcher("001000dfffff"), "MOVF") {};
void MOVF::execute(PIC10f200 *mcu) {
    Byte f = mcu->getDMEM(this->getf(mcu));

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), f);
    else mcu->setW(f);

    mcu->setZ(f == 0);
}

MOVWF::MOVWF() : InstructionHandler(InstructionMatcher("0000001fffff"), "MOVWF") {};
void MOVWF::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW();

    mcu->setDMEM(this->getf(mcu), W);
}

NOP::NOP() : InstructionHandler(InstructionMatcher("000000000000"), "NOP") {};
void NOP::execute(PIC10f200 *mcu) {}

RLF::RLF() : InstructionHandler(InstructionMatcher("001101dfffff"), "RLF") {};
void RLF::execute(PIC10f200 *mcu) {
    Byte f = mcu->getDMEM(this->getf(mcu));

    Byte result = (f << 1) + (mcu->getDMEM(REGISTERS::STATUS)[STATUSBITS::C] & 1);
    mcu->setC(f[7]);

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);
}

RRF::RRF() : InstructionHandler(InstructionMatcher("001100dfffff"), "RRF") {};
void RRF::execute(PIC10f200 *mcu) {
    Byte f = mcu->getDMEM(this->getf(mcu));

    Byte result = (f >> 1) + ((mcu->getDMEM(REGISTERS::STATUS)[STATUSBITS::C] & 1) << 7);
    mcu->setC(f[0]);

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);
}

SUBWF::SUBWF() : InstructionHandler(InstructionMatcher("000010dfffff"), "SUBWF") {};
void SUBWF::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW(), f = mcu->getDMEM(this->getf(mcu));

    Byte result = f - W;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
    mcu->setDC(Byte::digitBorrows(f, W));
    mcu->setC(Byte::borrows(f, W));
}

SWAPF::SWAPF() : InstructionHandler(InstructionMatcher("001110dfffff"), "SWAPF") {};
void SWAPF::execute(PIC10f200 *mcu) {
    Byte f = mcu->getDMEM(this->getf(mcu));

    Byte result = ((f & 0x0F) << 4) | ((f & 0xF0) >> 4);

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);
}

XORWF::XORWF() : InstructionHandler(InstructionMatcher("000110dfffff"), "XORWF") {};
void XORWF::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW(), f = mcu->getDMEM(this->getf(mcu));

    Byte result = W ^ f;

    if(this->getd(mcu)) mcu->setDMEM(this->getf(mcu), result);
    else mcu->setW(result);

    mcu->setZ(result == 0);
}

BCF::BCF() : InstructionHandler(InstructionMatcher("0100bbbfffff"), "BCF") {};
void BCF::execute(PIC10f200 *mcu) {
    Byte b = this->getb(mcu), f = mcu->getDMEM(this->getf(mcu));

    Byte result = f & ~(1 << b.get());

    mcu->setDMEM(this->getf(mcu), result);
}

BSF::BSF() : InstructionHandler(InstructionMatcher("0101bbbfffff"), "BSF") {};
void BSF::execute(PIC10f200 *mcu) {
    Byte b = this->getb(mcu), f = mcu->getDMEM(this->getf(mcu));

    Byte result = f | (1 << b.get());

    mcu->setDMEM(this->getf(mcu), result);
}

BTFSC::BTFSC() : InstructionHandler(InstructionMatcher("0110bbbfffff"), "BTFSC") {};
void BTFSC::execute(PIC10f200 *mcu) {
    // TODO
}

BTFSS::BTFSS() : InstructionHandler(InstructionMatcher("0111bbbfffff"), "BTFSS") {};
void BTFSS::execute(PIC10f200 *mcu) {
    // TODO
}

ANDLW::ANDLW() : InstructionHandler(InstructionMatcher("1110kkkkkkkk"), "ANDLW") {};
void ANDLW::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW();
    Word k = this->getk(mcu, 8);

    Byte result = W & k.get();

    mcu->setW(result);

    mcu->setZ(result == 0);
}

CALL::CALL() : InstructionHandler(InstructionMatcher("1001kkkkkkkk"), "CALL") {};
void CALL::execute(PIC10f200 *mcu) {
    // TODO
}

CLRWDT::CLRWDT() : InstructionHandler(InstructionMatcher("000000000100"), "CLRWDT") {};
void CLRWDT::execute(PIC10f200 *mcu) {
    // TODO
}

GOTO::GOTO() : InstructionHandler(InstructionMatcher("101kkkkkkkkk"), "GOTO") {};
void GOTO::execute(PIC10f200 *mcu) {
    Word k = this->getk(mcu, 9);
    mcu->setPC( k.get() );
}

IORLW::IORLW() : InstructionHandler(InstructionMatcher("1101kkkkkkkk"), "IORLW") {};
void IORLW::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW();
    Word k = this->getk(mcu, 8);

    Byte result = W | k.get();

    mcu->setW(result);

    mcu->setZ(result == 0);
}

MOVLW::MOVLW() : InstructionHandler(InstructionMatcher("1100kkkkkkkk"), "MOVLW") {};
void MOVLW::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW();
    Word k = this->getk(mcu, 8);

    Byte result = k.get();

    mcu->setW(result);
}

OPTION::OPTION() : InstructionHandler(InstructionMatcher("000000000010"), "OPTION") {};
void OPTION::execute(PIC10f200 *mcu) {
    mcu->setOption(mcu->getW());
}

RETLW::RETLW() : InstructionHandler(InstructionMatcher("1000kkkkkkkk"), "RETLW") {};
void RETLW::execute(PIC10f200 *mcu) {
    // TODO
}

SLEEP::SLEEP() : InstructionHandler(InstructionMatcher("000000000011"), "SLEEP") {};
void SLEEP::execute(PIC10f200 *mcu) {
    // TODO
}

TRIS::TRIS() : InstructionHandler(InstructionMatcher("000000000fff"), "TRIS") {};
void TRIS::execute(PIC10f200 *mcu) {
    Byte f = this->getf(mcu);
    
    // not sure what f being 6 or 7 should do
    mcu->setTris(mcu->getW());
}

XORLW::XORLW() : InstructionHandler(InstructionMatcher("1111kkkkkkkk"), "XORLW") {};
void XORLW::execute(PIC10f200 *mcu) {
    Byte W = mcu->getW();
    Word k = this->getk(mcu, 8);

    Byte result = W ^ k.get();

    mcu->setW(result);

    mcu->setZ(result == 0);
}

