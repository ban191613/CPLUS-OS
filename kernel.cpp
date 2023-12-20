#include "types.h"
#include "gdt.h"
#include "port.h"
#include "print.h"
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++) {
        (*i)();
    }
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber) {
    printf("hellow os!");
    GlobalDescriptionTable gdt;
    printf("hellow gdt!\n");
    
    while (1);
}