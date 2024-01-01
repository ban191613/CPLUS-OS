#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
#include "types.h"
#include "interrupts.h"
#include "port.h"
#include "driver.h"
#include "print.h"


class KeyBoardEventHandler
{
public:
    KeyBoardEventHandler();
    ~KeyBoardEventHandler();
    
    virtual void OnKeyDown(char)=0;
    virtual void OnKeyUp(char)=0;
};
class PrintKeyBoardEventHandler:public KeyBoardEventHandler
{
    public:
    PrintKeyBoardEventHandler();
    ~PrintKeyBoardEventHandler();
    
    void OnKeyDown(char);
    void OnKeyUp(char);

};
class KeyBoardDriver:public InterruptHandler,public Driver
{
public: 
    KeyBoardDriver(InterruptManger* interruptManger,KeyBoardEventHandler* keyBoardHandler);
    ~KeyBoardDriver();
    uint32_t HandleInterrupt(uint32_t esp);

    void Activate();
    void Reset();
    void Deactivate();
protected:
    Port8Bit dataProt;
    Port8Bit commandPort;
    KeyBoardEventHandler* keyBoardHandler;
};

#endif // !__KEYBOARD_H__