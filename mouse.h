#ifndef __MOUSE_H__
#define __MOUSE_H__
#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "print.h"
class MouseDriver:public InterruptHandler
{
public: 
    MouseDriver(InterruptManger* interruptManger);
    ~MouseDriver();
    uint32_t HandleInterrupt(uint32_t esp);
protected:
    Port8Bit dataProt;
    Port8Bit commandPort;

    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;
    int8_t x;
    int8_t y;
};

#endif // !__MOUSE_H__