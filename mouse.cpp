#include "mouse.h"

MouseDriver::MouseDriver(InterruptManger* interruptManger)
    :InterruptHandler(0x0c+interruptManger->HardwareInterruptOffset(),interruptManger),
    dataProt(0x60),   //8042芯片
    commandPort(0x64),
    offset(0),
    buttons(0),
    x(40),
    y(12)
{
    
    VideoMemory[y*80+x]=((VideoMemory[y*80+x]&0xf000)>>4)|((VideoMemory[y*80+x]&0x0f00)<<4)|(VideoMemory[y*80+x]&0x00ff);
    commandPort.Write(0xa8);  //active mouse
    commandPort.Write(0x20);
    
    uint8_t status = (dataProt.Read() | 2) & ~0x20;
    commandPort.Write(0x60);
    dataProt.Write(status);

    commandPort.Write(0xd4);
    dataProt.Write(0xf4);
    dataProt.Read();
}
MouseDriver::~MouseDriver()
{

}
uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status=commandPort.Read();    
    if(!(status&0x20)) 
        return esp;
    buffer[offset]=dataProt.Read();
    offset=(offset+1)%3;
    if(offset==0)
    {
        VideoMemory[y*80+x]=((VideoMemory[y*80+x]&0xf000)>>4)|((VideoMemory[y*80+x]&0x0f00)<<4)|(VideoMemory[y*80+x]&0x00ff);
        x+=buffer[1];
        if(x<0) x=0;
        else if(x>=80) x=79;
        y-=buffer[2];
        if(y<0) y=0;
        else if(y>=25) y=24;
        VideoMemory[y*80+x]=((VideoMemory[y*80+x]&0xf000)>>4)|((VideoMemory[y*80+x]&0x0f00)<<4)|(VideoMemory[y*80+x]&0x00ff);
        for(uint8_t i=0;i<3;i++)
        {
            if(buffer[0]&(1<<i)!=buttons&(1<<i)) //push down
            {
                    
            }
        }
        buttons=buffer[0];
    }
    
    // buffer

    return esp;
}
