#include "common/print.h"
uint16_t *VideoMemory = (uint16_t *)0xb8000; // 显示器内存开始地址地址
void printf(const char *str)
{

    static uint8_t x = 0, y = 0;
    for (int i = 0; str[i]; i++)
    {
        switch (str[i])
        {
        case '\n':
            y++;
            x = 0;
            break;

        default:
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
            x++;
        }

        if (x > 80)
        {
            x = 0;
            y++;
        }
        if (y >= 25)
        {
            for (y = 0; y < 25; y++)
            {
                for (x = 0; x < 88; x++)
                {
                    VideoMemory[i] = (VideoMemory[i] & 0xFF00) | ' ';
                }
            }
            x = 0, y = 0;
        }
    }
}
void printf(uint8_t num)
{
    const char *dex = "0123456789";
    char *f = (char *)" ";
    while (num)
    {
        f[0] = dex[num % 10];
        printf((const char *)f);
        num = num / 10;
    }
}
void printf(uint16_t num)
{
    const char *dex = "0123456789";
    char *f = (char *)" ";
    while (num)
    {
        f[0] = dex[num % 10];
        printf((const char *)f);
        num = num / 10;
    }
}
void printfHex(uint8_t key)
{
    char *foo = (char *)"00";
    const char *hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0f];
    foo[1] = hex[key & 0x0f];
    printf((const char *)foo);
}
void printfHex(uint16_t key)
{
    printfHex((uint8_t)(key));
    printfHex((uint8_t)(key >> 8));
}
void printfHex(uint32_t key)
{
    printfHex((uint16_t)(key));
    printfHex((uint16_t)(key >> 16));
}
void printfHex(uint64_t key)
{
    printfHex((uint32_t)(key));
    printfHex((uint32_t)(key >> 32));
}