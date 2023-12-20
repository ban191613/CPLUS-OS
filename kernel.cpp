#include "types.h"
#include "gdt.h"
#include "port.h"
#include "print.h"
#include "interrupts.h"
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernelMain(void* multiBoot_structure, uint32_t magicNumber) {
    printf("hi os!");
    GlobalDescriptionTable gdt;
    printf("hi gdt!\n");
    InterruptManger idt(0x20,&gdt);
    while (1);
}