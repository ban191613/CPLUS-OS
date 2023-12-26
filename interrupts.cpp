#include "interrupts.h"
#include "print.h"
#include "port.h"
InterruptManger::GateDescriptor InterruptManger::interruptDescriptorTable[256];
InterruptManger::InterruptManger(uint16_t hardwareInterruptOffset, GlobalDescriptionTable *gdt)
    :picMasterCommand(0x20),
    picMasterData(0x21),
    picSlaveCommand(0xA0),
    picSlaveData(0xA1)
{
    
    uint16_t codeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE=0xe;  
    for (uint16_t i = 0; i < 256; i++) {
        SetInterruptDescriptorTableEntry(i, codeSegment, nullptr, 0, IDT_INTERRUPT_GATE);
    }
    
    

    SetInterruptDescriptorTableEntry(0x00, codeSegment, &HandleException0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x01, codeSegment, &HandleException0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x02, codeSegment, &HandleException0x02, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x03, codeSegment, &HandleException0x03, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x04, codeSegment, &HandleException0x04, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x05, codeSegment, &HandleException0x05, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x06, codeSegment, &HandleException0x06, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x07, codeSegment, &HandleException0x07, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x08, codeSegment, &HandleException0x08, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x09, codeSegment, &HandleException0x09, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0A, codeSegment, &HandleException0x0A, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0B, codeSegment, &HandleException0x0B, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0C, codeSegment, &HandleException0x0C, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0D, codeSegment, &HandleException0x0D, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0E, codeSegment, &HandleException0x0E, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x0F, codeSegment, &HandleException0x0F, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x10, codeSegment, &HandleException0x10, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x11, codeSegment, &HandleException0x11, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x12, codeSegment, &HandleException0x12, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(0x13, codeSegment, &HandleException0x13, 0, IDT_INTERRUPT_GATE);


    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x00, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x01, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x02, codeSegment, &HandleInterruptRequest0x02, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x03, codeSegment, &HandleInterruptRequest0x03, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x04, codeSegment, &HandleInterruptRequest0x04, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x05, codeSegment, &HandleInterruptRequest0x05, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x06, codeSegment, &HandleInterruptRequest0x06, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x07, codeSegment, &HandleInterruptRequest0x07, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x08, codeSegment, &HandleInterruptRequest0x08, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x09, codeSegment, &HandleInterruptRequest0x09, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0A, codeSegment, &HandleInterruptRequest0x0A, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0B, codeSegment, &HandleInterruptRequest0x0B, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0C, codeSegment, &HandleInterruptRequest0x0C, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0D, codeSegment, &HandleInterruptRequest0x0D, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0E, codeSegment, &HandleInterruptRequest0x0E, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x0F, codeSegment, &HandleInterruptRequest0x0F, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntry(hardwareInterruptOffset + 0x31, codeSegment, &HandleInterruptRequest0x31, 0, IDT_INTERRUPT_GATE);
    
    picMasterCommand.write(0x11);
    picSlaveCommand.write(0x11);

    picMasterData.write(hardwareInterruptOffset);
    picSlaveData.write(hardwareInterruptOffset+8);

    picMasterData.write(0x04);
    picSlaveData.write(0x02);

    picMasterData.write(0x01);
    picSlaveData.write(0x01);

    picMasterData.write(0x00);
    picSlaveData.write(0x00);



    InterruptDescriptorTablePoint idt;
    idt.size=256*sizeof(GateDescriptor)-1;
    idt.base=(uint32_t)interruptDescriptorTable;
    asm volatile("lidt %0"::"m" (idt));


}
InterruptManger::~InterruptManger()
{

}
void InterruptManger::Active()
{
    asm("sti");
}
uint32_t InterruptManger::HandleInterrupt(uint8_t interruptNumber,uint32_t esp)
{
    uint32_t result;
    printf("interrupt!");
    return esp;  
}
void InterruptManger::SetInterruptDescriptorTableEntry(uint8_t interruptNumber,
                        uint16_t codeSegmentSelectorOffset,
                        void(*handler)(),
                        uint8_t DescriptorPrivilegeLevel,
                        uint8_t DescriptorType)
{
    const uint8_t IDT_DESC_PRESENT=0x80;

    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xffff;
    interruptDescriptorTable[interruptNumber].handlerAddressHighBits = ((uint32_t)handler >> 16) & 0xffff;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | ((DescriptorPrivilegeLevel & 3) << 5) | DescriptorType;
    interruptDescriptorTable[interruptNumber].reserved = 0;

}

