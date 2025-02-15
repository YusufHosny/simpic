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
    InstructionHandler(InstructionMatcher matcher);

    bool match(const Word input) const;
    virtual void execute(PIC10f200 *mcu) = 0;
};

class NOP : public InstructionHandler {
public:
    NOP();
    void execute(PIC10f200 *mcu) override;
};

class MOVLW : public InstructionHandler {
public:
    MOVLW();
    void execute(PIC10f200 *mcu) override;
};

class ANDLW : public InstructionHandler {
public:
    ANDLW();
    void execute(PIC10f200 *mcu) override;
};

class IORLW : public InstructionHandler {
public:
    IORLW();
    void execute(PIC10f200 *mcu) override;
};

class XORLW : public InstructionHandler {
public:
    XORLW();
    void execute(PIC10f200 *mcu) override;
};

class GOTO : public InstructionHandler {
public:
    GOTO();
    void execute(PIC10f200 *mcu) override;
};
