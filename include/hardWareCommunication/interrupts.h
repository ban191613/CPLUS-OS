#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include "types.h"
#include "port.h"
#include "gdt.h"
class InterruptManger;
class InterruptHandler
{
public:
    virtual uint32_t HandleInterrupt(uint32_t esp);   
protected:
    InterruptHandler(uint8_t interruptNumber,InterruptManger* interruptManger);
    ~InterruptHandler();


    InterruptManger* interruptManger;
    uint8_t interruptNumber;
   
    
};

class InterruptManger
{
   friend class InterruptHandler;
public:   
    InterruptManger(uint16_t hardwareInterruptOffset, GlobalDescriptionTable *gdt);
    ~InterruptManger();

    void Active();
    void DeActive();
    uint16_t HardwareInterruptOffset();
protected:
    static InterruptManger* activeInterruptManger;
    InterruptHandler* handles[256];
    struct GateDescriptor
    {
    public:
        uint16_t handlerAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;
        uint8_t access;
        uint16_t handlerAddressHighBits;
        
    }__attribute__((packed));

    static void SetInterruptDescriptorTableEntry(
                uint8_t interruptNumber,
                uint16_t codeSegmentSelectorOffset,
                void (*handler)(),
                uint8_t DescriptorPrivilegeLevel,
                uint8_t DescriptorType
            );
    
    static GateDescriptor interruptDescriptorTable[256];
    struct InterruptDescriptorTablePoint
    {
        uint16_t size;
        uint32_t base;
    }__attribute__((packed));
    
    
    uint16_t hardwareInterruptOffset;
    static void InterruptIgnore();
    static uint32_t HandleInterrupt(uint8_t interruptNumber,uint32_t esp);
    
    uint32_t DoHandleInterrupt(uint8_t interruptNumber,uint32_t esp);
    
    //define in interruption.s

    static void InterruptTest();
    

    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
    static void HandleInterruptRequest0x02();
    static void HandleInterruptRequest0x03();
    static void HandleInterruptRequest0x04();
    static void HandleInterruptRequest0x05();
    static void HandleInterruptRequest0x06();
    static void HandleInterruptRequest0x07();
    static void HandleInterruptRequest0x08();
    static void HandleInterruptRequest0x09();
    static void HandleInterruptRequest0x0A();
    static void HandleInterruptRequest0x0B();
    static void HandleInterruptRequest0x0C();
    static void HandleInterruptRequest0x0D();
    static void HandleInterruptRequest0x0E();
    static void HandleInterruptRequest0x0F();
    static void HandleInterruptRequest0x31();

    static void HandleException0x00();
    static void HandleException0x01();
    static void HandleException0x02();
    static void HandleException0x03();
    static void HandleException0x04();
    static void HandleException0x05();
    static void HandleException0x06();
    static void HandleException0x07();
    static void HandleException0x08();
    static void HandleException0x09();
    static void HandleException0x0A();
    static void HandleException0x0B();
    static void HandleException0x0C();
    static void HandleException0x0D();
    static void HandleException0x0E();
    static void HandleException0x0F();
    static void HandleException0x10();
    static void HandleException0x11();
    static void HandleException0x12();
    static void HandleException0x13();

    Port8BitSLow picMasterCommand;
    Port8BitSLow picMasterData;
    Port8BitSLow picSlaveCommand;
    Port8BitSLow picSlaveData;
};




#endif // !__INTERRUPTS_H__