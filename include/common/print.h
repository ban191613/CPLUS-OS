#if !defined(__PRINT_H__)
#define __PRINT_H__
#include "common/types.h"

extern uint16_t *VideoMemory;
void printf(const char *str);
void printf(uint8_t num);
void printf(uint16_t num);

void printfHex(uint8_t key);
void printfHex(uint16_t key);
void printfHex(uint32_t key);
void printfHex(uint64_t key);
#endif // __PRINT_H__
