#pragma once

#include <iostream>
#include <bitset>
#include <stdexcept>
#include <inttypes.h>

class Byte {
private:
    uint8_t value;

public:
    Byte(uint8_t v = 0) : value(v) {}
    
    uint8_t get() const { return value; }
    void set(uint8_t v) { value = v; }
    
    bool operator[](size_t index) const {
        if (index >= 8) throw std::out_of_range("Bit index out of range");
        return (value >> index) & 1;
    }
    
    void setBit(size_t index, bool bit) {
        if (index >= 8) throw std::out_of_range("Bit index out of range");
        if (bit)
            value |= (1 << index);
        else
            value &= ~(1 << index);
    }
    
    Byte operator+(const Byte &b) const { return Byte(value + b.value); }
    Byte operator-(const Byte &b) const { return Byte(value - b.value); }
    Byte operator&(const Byte &b) const { return Byte(value & b.value); }
    Byte operator|(const Byte &b) const { return Byte(value | b.value); }
    Byte operator^(const Byte &b) const { return Byte(value ^ b.value); }
    Byte operator~() const { return Byte(~value); }
    Byte operator<<(size_t shift) const { return Byte(value << shift); }
    Byte operator>>(size_t shift) const { return Byte(value >> shift); }
    
    auto operator<=>(const Byte &b) const = default;
    
    Byte& operator+=(const Byte &b) { value += b.value; return *this; }
    Byte& operator-=(const Byte &b) { value -= b.value; return *this; }
    Byte& operator&=(const Byte &b) { value &= b.value; return *this; }
    Byte& operator|=(const Byte &b) { value |= b.value; return *this; }
    Byte& operator^=(const Byte &b) { value ^= b.value; return *this; }
    Byte& operator<<=(size_t shift) { value <<= shift; return *this; }
    Byte& operator>>=(size_t shift) { value >>= shift; return *this; }
    
    friend std::ostream& operator<<(std::ostream &os, const Byte &b) {
        os << std::bitset<8>(b.value);
        return os;
    }
};

/*
    16-bit word wrapper for the 12-bit word used in the PIC
    internally everything is handled using the 16-bit word, which is only converted on access
*/
class Word {
private:
    uint16_t value;

public:
    Word(uint16_t v = 0) : value(v) {}
    
    uint16_t get() const { return value & 0xFFF; }
    void set(uint16_t v) { value = v & 0xFFF; }
    
    Byte high() const { return Byte((value >> 8) & 0xFF); }
    Byte low() const { return Byte(value & 0xFF); }

    bool operator[](size_t index) const {
        if (index >= 12) throw std::out_of_range("Bit index out of range");
        return (value >> index) & 1;
    }
    
    void setBit(size_t index, bool bit) {
        if (index >= 12) throw std::out_of_range("Bit index out of range");
        if (bit)
            value |= (1 << index);
        else
            value &= ~(1 << index);
    }
    
    Word operator+(const Word &w) const { return Word(value + w.value); }
    Word operator-(const Word &w) const { return Word(value - w.value); }
    Word operator&(const Word &w) const { return Word(value & w.value); }
    Word operator|(const Word &w) const { return Word(value | w.value); }
    Word operator^(const Word &w) const { return Word(value ^ w.value); }
    Word operator~() const { return Word(~value); }
    Word operator<<(size_t shift) const { return Word(value << shift); }
    Word operator>>(size_t shift) const { return Word(value >> shift); }
    
    auto operator<=>(const Word &w) const = default;
    
    Word& operator+=(const Word &w) { value += w.value; return *this; }
    Word& operator-=(const Word &w) { value -= w.value; return *this; }
    Word& operator&=(const Word &w) { value &= w.value; return *this; }
    Word& operator|=(const Word &w) { value |= w.value; return *this; }
    Word& operator^=(const Word &w) { value ^= w.value; return *this; }
    Word& operator<<=(size_t shift) { value <<= shift; return *this; }
    Word& operator>>=(size_t shift) { value >>= shift; return *this; }
    
    friend std::ostream& operator<<(std::ostream &os, const Word &w) {
        os << std::bitset<12>(w.value & 0xFFF);
        return os;
    }
};


