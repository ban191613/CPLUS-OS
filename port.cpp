#include "port.h"

Port::Port(uint16_t portNumber)
    :portNumber(portNumber){}

Port::~Port() {}

Port8Bit::Port8Bit(uint16_t portNumber)
    :Port(portNumber){}
Port8Bit::~Port8Bit()
{}


Port8BitSLow::Port8BitSLow(uint16_t portNumber)
    :Port8Bit(portNumber){}
Port8BitSLow::~Port8BitSLow()
{}


Port16Bit::Port16Bit(uint16_t portNumber)
    :Port(portNumber){}
Port16Bit::~Port16Bit()
{}



Port32Bit::Port32Bit(uint16_t portNumber)
    :Port(portNumber){}
Port32Bit::~Port32Bit()
{}

void Port8Bit::write(uint8_t data)
{
    asm volatile("outb %0,%1":"=a"(data):"Nd"(portNumber));
}
uint8_t Port8Bit::read()
{
    uint8_t result;
    asm volatile("inb %1,%0":"=a"(result):"Nd"(portNumber));
    return result;
}

void Port8BitSLow::write(uint8_t data)
{
    asm volatile("outb %0,%1\njmp 1f\n1: jmp 1f\n1:":"=a"(data):"Nd"(portNumber));
}


void Port16Bit::write(uint16_t data)
{
    asm volatile("outw %0,%1":"=a"(data):"Nd"(portNumber));
}
uint16_t Port16Bit::read()
{
    uint16_t result;
    asm volatile("inw %1,%0":"=a"(result):"Nd"(portNumber));
    return result;
}

void Port32Bit::write(uint32_t data)
{
    asm volatile("outl %0,%1":"=a"(data):"Nd"(portNumber));
}
uint32_t Port32Bit::read()
{
    uint32_t result;
    asm volatile("inl %1,%0":"=a"(result):"Nd"(portNumber));
    return result;
}

