#pragma once

#include <string>
#include <functional>
#include "types.hpp"

class PIC10f200;

class InstructionMatcher {
private:
    const std::string matchOn;

public:
    InstructionMatcher(std::string matchOn);

    bool match(const Word input) const;
};

class InstructionHandler {
protected:
    const InstructionMatcher matcher;

public:
    InstructionHandler(InstructionMatcher matcher, const std::string mnemonic);

    const std::string mnemonic;

    bool match(const Word input) const;
    virtual void execute(PIC10f200 *mcu) = 0;

    Byte getf(PIC10f200 *mcu);
    Word getk(PIC10f200 *mcu, uint8_t length);
    bool getd(PIC10f200 *mcu);
    Byte getb(PIC10f200 *mcu);
};

class ADDWF : public InstructionHandler {
public:
    ADDWF();
    void execute(PIC10f200 *mcu) override;
};

class ANDWF : public InstructionHandler {
public:
    ANDWF();
    void execute(PIC10f200 *mcu) override;
};

class CLRF : public InstructionHandler {
public:
    CLRF();
    void execute(PIC10f200 *mcu) override;
};
    
class CLRW : public InstructionHandler {
public:
    CLRW();
    void execute(PIC10f200 *mcu) override;
};

class COMF : public InstructionHandler {
public:
    COMF();
    void execute(PIC10f200 *mcu) override;
};
    
class DECF : public InstructionHandler {
public:
    DECF();
    void execute(PIC10f200 *mcu) override;
};

class DECFSZ : public InstructionHandler {
public:
    DECFSZ();
    void execute(PIC10f200 *mcu) override;
};
    
class INCF : public InstructionHandler {
public:
    INCF();
    void execute(PIC10f200 *mcu) override;
};

class INCFSZ : public InstructionHandler {
public:
    INCFSZ();
    void execute(PIC10f200 *mcu) override;
};
    
class IORWF : public InstructionHandler {
public:
    IORWF();
    void execute(PIC10f200 *mcu) override;
};

class MOVF : public InstructionHandler {
public:
    MOVF();
    void execute(PIC10f200 *mcu) override;
};
    
class MOVWF : public InstructionHandler {
public:
    MOVWF();
    void execute(PIC10f200 *mcu) override;
};

class NOP : public InstructionHandler {
public:
    NOP();
    void execute(PIC10f200 *mcu) override;
};

class RLF : public InstructionHandler {
public:
    RLF();
    void execute(PIC10f200 *mcu) override;
};
    
class RRF : public InstructionHandler {
public:
    RRF();
    void execute(PIC10f200 *mcu) override;
};

class SUBWF : public InstructionHandler {
public:
    SUBWF();
    void execute(PIC10f200 *mcu) override;
};
    
class SWAPF : public InstructionHandler {
public:
    SWAPF();
    void execute(PIC10f200 *mcu) override;
};

class XORWF : public InstructionHandler {
public:
    XORWF();
    void execute(PIC10f200 *mcu) override;
};
    
class BCF : public InstructionHandler {
public:
    BCF();
    void execute(PIC10f200 *mcu) override;
};

class BSF : public InstructionHandler {
public:
    BSF();
    void execute(PIC10f200 *mcu) override;
};
    
class BTFSC : public InstructionHandler {
public:
    BTFSC();
    void execute(PIC10f200 *mcu) override;
};

class BTFSS : public InstructionHandler {
public:
    BTFSS();
    void execute(PIC10f200 *mcu) override;
};


class ANDLW : public InstructionHandler {
public:
    ANDLW();
    void execute(PIC10f200 *mcu) override;
};

class CALL : public InstructionHandler {
public:
    CALL();
    void execute(PIC10f200 *mcu) override;
};

    
class CLRWDT : public InstructionHandler {
public:
    CLRWDT();
    void execute(PIC10f200 *mcu) override;
};

class GOTO : public InstructionHandler {
public:
    GOTO();
    void execute(PIC10f200 *mcu) override;
};

class IORLW : public InstructionHandler {
public:
    IORLW();
    void execute(PIC10f200 *mcu) override;
};

class MOVLW : public InstructionHandler {
public:
    MOVLW();
    void execute(PIC10f200 *mcu) override;
};

class OPTION : public InstructionHandler {
public:
    OPTION();
    void execute(PIC10f200 *mcu) override;
};
    
class SLEEP : public InstructionHandler {
public:
    SLEEP();
    void execute(PIC10f200 *mcu) override;
};

class TRIS : public InstructionHandler {
public:
    TRIS();
    void execute(PIC10f200 *mcu) override;
};
    
class RETLW : public InstructionHandler {
public:
    RETLW();
    void execute(PIC10f200 *mcu) override;
};

class XORLW : public InstructionHandler {
public:
    XORLW();
    void execute(PIC10f200 *mcu) override;
};

