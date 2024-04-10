#include "drivers/keyboard.h"
KeyBoardEventHandler::KeyBoardEventHandler()
{
}

KeyBoardEventHandler::~KeyBoardEventHandler()
{
}

PrintKeyBoardEventHandler::PrintKeyBoardEventHandler()
{
}

PrintKeyBoardEventHandler::~PrintKeyBoardEventHandler()
{
}
void PrintKeyBoardEventHandler::OnKeyDown(char m_char)
{
    printf((const char *)&m_char);
}
void PrintKeyBoardEventHandler::OnKeyUp(char m_char)
{
    printf((const char *)&m_char);
}
KeyBoardDriver::KeyBoardDriver(InterruptManger *interruptManger, KeyBoardEventHandler *keyBoardHandler)
    : InterruptHandler(0x01 + interruptManger->HardwareInterruptOffset(), interruptManger), dataProt(0x60),
      commandPort(0x64), keyBoardHandler(keyBoardHandler)
{
    this->Reset();
}
KeyBoardDriver::~KeyBoardDriver()
{
}
uint32_t KeyBoardDriver::HandleInterrupt(uint32_t esp)
{

    uint8_t key = dataProt.Read();
    if (keyBoardHandler == nullptr)
        return esp;

    static bool shift = false;
    switch (key)
    {
    case 0x02:
        if (shift)
            keyBoardHandler->OnKeyDown('!');
        else
            keyBoardHandler->OnKeyDown('1');
        break;
    case 0x03:
        if (shift)
            keyBoardHandler->OnKeyDown('@');
        else
            keyBoardHandler->OnKeyDown('2');
        break;
    case 0x04:
        if (shift)
            keyBoardHandler->OnKeyDown('#');
        else
            keyBoardHandler->OnKeyDown('3');
        break;
    case 0x05:
        if (shift)
            keyBoardHandler->OnKeyDown('$');
        else
            keyBoardHandler->OnKeyDown('4');
        break;
    case 0x06:
        if (shift)
            keyBoardHandler->OnKeyDown('%');
        else
            keyBoardHandler->OnKeyDown('5');
        break;
    case 0x07:
        if (shift)
            keyBoardHandler->OnKeyDown('^');
        else
            keyBoardHandler->OnKeyDown('6');
        break;
    case 0x08:
        if (shift)
            keyBoardHandler->OnKeyDown('&');
        else
            keyBoardHandler->OnKeyDown('7');
        break;
    case 0x09:
        if (shift)
            keyBoardHandler->OnKeyDown('*');
        else
            keyBoardHandler->OnKeyDown('8');
        break;
    case 0x0A:
        if (shift)
            keyBoardHandler->OnKeyDown('(');
        else
            keyBoardHandler->OnKeyDown('9');
        break;
    case 0x0B:
        if (shift)
            keyBoardHandler->OnKeyDown(')');
        else
            keyBoardHandler->OnKeyDown('0');
        break;

    case 0x10:
        if (shift)
            keyBoardHandler->OnKeyDown('Q');
        else
            keyBoardHandler->OnKeyDown('q');
        break;
    case 0x11:
        if (shift)
            keyBoardHandler->OnKeyDown('W');
        else
            keyBoardHandler->OnKeyDown('w');
        break;
    case 0x12:
        if (shift)
            keyBoardHandler->OnKeyDown('E');
        else
            keyBoardHandler->OnKeyDown('e');
        break;
    case 0x13:
        if (shift)
            keyBoardHandler->OnKeyDown('R');
        else
            keyBoardHandler->OnKeyDown('r');
        break;
    case 0x14:
        if (shift)
            keyBoardHandler->OnKeyDown('T');
        else
            keyBoardHandler->OnKeyDown('t');
        break;
    case 0x15:
        if (shift)
            keyBoardHandler->OnKeyDown('Z');
        else
            keyBoardHandler->OnKeyDown('z');
        break;
    case 0x16:
        if (shift)
            keyBoardHandler->OnKeyDown('U');
        else
            keyBoardHandler->OnKeyDown('u');
        break;
    case 0x17:
        if (shift)
            keyBoardHandler->OnKeyDown('I');
        else
            keyBoardHandler->OnKeyDown('i');
        break;
    case 0x18:
        if (shift)
            keyBoardHandler->OnKeyDown('O');
        else
            keyBoardHandler->OnKeyDown('o');
        break;
    case 0x19:
        if (shift)
            keyBoardHandler->OnKeyDown('P');
        else
            keyBoardHandler->OnKeyDown('p');
        break;

    case 0x1E:
        if (shift)
            keyBoardHandler->OnKeyDown('A');
        else
            keyBoardHandler->OnKeyDown('a');
        break;
    case 0x1F:
        if (shift)
            keyBoardHandler->OnKeyDown('S');
        else
            keyBoardHandler->OnKeyDown('s');
        break;
    case 0x20:
        if (shift)
            keyBoardHandler->OnKeyDown('D');
        else
            keyBoardHandler->OnKeyDown('d');
        break;
    case 0x21:
        if (shift)
            keyBoardHandler->OnKeyDown('F');
        else
            keyBoardHandler->OnKeyDown('f');
        break;
    case 0x22:
        if (shift)
            keyBoardHandler->OnKeyDown('G');
        else
            keyBoardHandler->OnKeyDown('g');
        break;
    case 0x23:
        if (shift)
            keyBoardHandler->OnKeyDown('H');
        else
            keyBoardHandler->OnKeyDown('h');
        break;
    case 0x24:
        if (shift)
            keyBoardHandler->OnKeyDown('J');
        else
            keyBoardHandler->OnKeyDown('j');
        break;
    case 0x25:
        if (shift)
            keyBoardHandler->OnKeyDown('K');
        else
            keyBoardHandler->OnKeyDown('k');
        break;
    case 0x26:
        if (shift)
            keyBoardHandler->OnKeyDown('L');
        else
            keyBoardHandler->OnKeyDown('l');
        break;

    case 0x2C:
        if (shift)
            keyBoardHandler->OnKeyDown('Y');
        else
            keyBoardHandler->OnKeyDown('y');
        break;
    case 0x2D:
        if (shift)
            keyBoardHandler->OnKeyDown('X');
        else
            keyBoardHandler->OnKeyDown('x');
        break;
    case 0x2E:
        if (shift)
            keyBoardHandler->OnKeyDown('C');
        else
            keyBoardHandler->OnKeyDown('c');
        break;
    case 0x2F:
        if (shift)
            keyBoardHandler->OnKeyDown('V');
        else
            keyBoardHandler->OnKeyDown('v');
        break;
    case 0x30:
        if (shift)
            keyBoardHandler->OnKeyDown('B');
        else
            keyBoardHandler->OnKeyDown('b');
        break;
    case 0x31:
        if (shift)
            keyBoardHandler->OnKeyDown('N');
        else
            keyBoardHandler->OnKeyDown('n');
        break;
    case 0x32:
        if (shift)
            keyBoardHandler->OnKeyDown('M');
        else
            keyBoardHandler->OnKeyDown('m');
        break;
    case 0x33:
        if (shift)
            keyBoardHandler->OnKeyDown('<');
        else
            keyBoardHandler->OnKeyDown(',');
        break;
    case 0x34:
        if (shift)
            keyBoardHandler->OnKeyDown('>');
        else
            keyBoardHandler->OnKeyDown('.');
        break;
    case 0x35:
        if (shift)
            keyBoardHandler->OnKeyDown('_');
        else
            keyBoardHandler->OnKeyDown('-');
        break;

    case 0x1C:
        keyBoardHandler->OnKeyDown('\n');
        break;
    case 0x39:
        keyBoardHandler->OnKeyDown(' ');
        break;
    case 0x2A:
    case 0x36:
        shift = true;
        break;
    case 0xAA:
    case 0xB6:
        shift = false;
        break;

    case 0x45:
        break; // NumLock

    default:
        if (key < 0x80)
        {
            printf("KEYBOARD 0x");
            printfHex(key);
        }
    }
    return esp;
}
void KeyBoardDriver::Activate()
{
}
void KeyBoardDriver::Reset()
{
    while (commandPort.Read() & 0x1)
    {
        dataProt.Read();
    }
    commandPort.Write(0xae); // active keyboard
    commandPort.Write(0x20);

    uint8_t status = (dataProt.Read() | 1) & ~0x10;
    commandPort.Write(0x60);
    dataProt.Write(status);
    dataProt.Write(0xf4);
}
void KeyBoardDriver::Deactivate()
{
}