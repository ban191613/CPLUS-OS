#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include "types.h"
#include "interrupts.h"
#include "port.h"

class KeyBoardDriver:public InterruptHandler
{
public: 
    KeyBoardDriver(InterruptManger* interruptManger);
    ~KeyBoardDriver();
    uint32_t HandleInterrupt(uint32_t esp);
protected:
    Port8Bit dataProt;
    Port8Bit commandPort;

};

#endif // !__KEYBOARD_H__