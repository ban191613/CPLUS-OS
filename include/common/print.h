#if !defined(__PRINT_H__)
#define __PRINT_H__
#include "types.h"

extern uint16_t *VideoMemory;
void printf(const char *str);
void printfHex(uint8_t key);
#endif // __PRINT_H__
