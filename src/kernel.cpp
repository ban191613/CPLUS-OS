#include "gdt.h"
#include "types.h"
#include "print.h"
#include "port.h"
#include "interrupts.h"
#include "keyboard.h"
#include "mouse.h"
#include "driver.h"
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
    {
        (*i)();
    }
}

extern "C" void kernelMain(void *multiBoot_structure, uint32_t magicNumber)
{
    printf("hi os!");
    GlobalDescriptionTable gdt;
    printf("hi gdt!\n");
    InterruptManger interrupt(0x20, &gdt);
    printf("hi idt!\n");
    PrintKeyBoardEventHandler printKeyBoardEventHandler;
    KeyBoardDriver keyboard(&interrupt, &printKeyBoardEventHandler);
    ClickMouseEventHandler clickMouseEventHandler;
    MouseDriver mouse(&interrupt, &clickMouseEventHandler);
    DriverManger driverManger;
    driverManger.AddDriver(&keyboard);
    driverManger.AddDriver(&mouse);
    driverManger.ActivateAll();
    interrupt.Active();

    while (1)
    {
        // printf("1");
    }
}