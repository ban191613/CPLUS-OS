#ifndef __PORT_H__
#define __PORT_H__
#include "types.h"


class Port
{

protected:
    uint16_t portNumber;
    Port(uint16_t portNumber);
    ~Port();
};

class Port8Bit:public Port
{
public:
    Port8Bit(uint16_t portNumber);
    ~Port8Bit();
    virtual void  Write(uint8_t data);
    virtual uint8_t Read();
};


class Port8BitSLow:public Port8Bit
{
public:
    Port8BitSLow(uint16_t portNumber);
    ~Port8BitSLow();
    virtual void  Write(uint8_t data);
};


class Port16Bit:public Port
{
public:
    Port16Bit(uint16_t portNumber);
    ~Port16Bit();
    virtual void Write(uint16_t data);
    virtual uint16_t Read();
};
class Port32Bit:public Port
{
public:
    Port32Bit(uint16_t portNumber);
    ~Port32Bit();
    virtual void Write(uint32_t data);
    virtual uint32_t Read();
};


#endif // !__PORT_H__