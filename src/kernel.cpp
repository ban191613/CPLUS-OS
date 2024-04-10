#include "common/print.h"
#include "common/types.h"
#include "drivers/amd_am79c973.h"
#include "drivers/driver.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "gdt.h"
#include "hardWareCommunication/interrupts.h"
#include "hardWareCommunication/pci.h"
#include "hardWareCommunication/port.h"
#include "memorymanger.h"
#include "multitask.h"
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
// #define TASK_TEST
#ifdef TASK_TEST
void taskFunction1()
{
    while (true)
    {
        printf("A");
    }
}
void taskFunction2()
{
    while (true)
    {
        printf("B");
    }
}
#endif // TASK_TEST

extern "C" void kernelMain(void *multiBoot_structure, uint32_t magicNumber)
{
    printf("hi os!");
    GlobalDescriptionTable gdt;
    printf("hi gdt!\n");

    size_t heap = 10 * 1024 * 1024;
    uint32_t *memoryUpper = (uint32_t *)((uint32_t)multiBoot_structure + 8);
    MemoryManger activeMemoryManger(heap, (*memoryUpper) * 1024 - heap - 10 * 1024);

    TaskManger taskManger;
#ifdef TASK_TEST
    Task task1(&gdt, taskFunction1);
    Task task2(&gdt, taskFunction2);
    taskManger.AddTask(&task1);
    taskManger.AddTask(&task2);
#endif // TASK_TEST

    InterruptManger interruptManger(0x20, &gdt, &taskManger);
    printf("hi idt!\n");

    PrintKeyBoardEventHandler printKeyBoardEventHandler;
    KeyBoardDriver keyboard(&interruptManger, &printKeyBoardEventHandler);

    ClickMouseEventHandler clickMouseEventHandler;
    MouseDriver mouse(&interruptManger, &clickMouseEventHandler); //此处传入的clickMouseEventHandler，动作事件也就是这个

    DriverManger driverManger;
    driverManger.AddDriver(&keyboard);
    driverManger.AddDriver(&mouse);

    // printf("\n heap: 0x");
    // printfHex((uint32_t)heap);
    // printf("\n");
    // void *allocated = activeMemoryManger.malloc(1024);
    // printf("\n allocated: 0x");
    // printfHex((uint32_t)allocated);
    // printf("\n");

    PeripheralCommentInterconnectControl pic;
    pic.SelectDriver(&driverManger, &interruptManger);
    // class amd_am79c973;
    // amd_am79c973 *eth0 = (amd_am79c973 *)(driverManger.drivers[2]);
    // eth0->Send((uint8_t *)"Hello NetWork", 13);

    driverManger.ActivateAll();
    interruptManger.Active();
    while (1)
    {
        // printf("1");
    }
}