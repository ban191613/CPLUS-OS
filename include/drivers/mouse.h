#ifndef __MOUSE_H__
#define __MOUSE_H__
#include "common/types.h"
#include "hardWareCommunication/interrupts.h"
#include "hardWareCommunication/port.h"
#include "common/print.h"
#include "drivers/driver.h"


class MouseEventHandler
{
public:
    MouseEventHandler();
    ~MouseEventHandler();
    
    virtual void OnActivate(void)=0;
    virtual void OnMouseDown(uint8_t button)=0;
    virtual void OnMouseUp(uint8_t button)=0;
    virtual void OnMouseMove(uint8_t buffer1,uint8_t buffer2)=0;

};
class ClickMouseEventHandler:public MouseEventHandler
{
public:
    ClickMouseEventHandler();
    ~ClickMouseEventHandler();
    
    void OnActivate(void);
    void OnMouseDown(uint8_t button);
    void OnMouseUp(uint8_t button);
    void OnMouseMove(uint8_t buffer1,uint8_t buffer2);
protected:
    int8_t x;
    int8_t y;
};

class MouseDriver:public InterruptHandler,public Driver
{
public: 
    MouseDriver(InterruptManger* interruptManger,MouseEventHandler* mouseEventHandler);
    ~MouseDriver();
    uint32_t HandleInterrupt(uint32_t esp);

    void Activate();
    void Reset();
    void Deactivate();
protected:
    Port8Bit dataProt;
    Port8Bit commandPort;

    uint8_t buffer[3];
    uint8_t offset;
    uint8_t buttons;
    int8_t x;
    int8_t y;

    MouseEventHandler* mouseEventHandler;
};

#endif // !__MOUSE_H__