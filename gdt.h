#ifndef __GDT_H__     
#define __GDT_H__
#include "types.h"
class GlobalDescriptionTable
{
public:
    GlobalDescriptionTable();
    ~GlobalDescriptionTable();
    
    class SegmentDescriptor
    {
    public:
        SegmentDescriptor(uint32_t base,uint32_t limit,uint8_t type);
        uint32_t Base();
        uint32_t Limit();
    private:
        uint16_t limit_l;
        uint16_t base_l;
        uint8_t base_m;
        uint8_t type; 
        uint8_t flag_limit_h;  //可以使用结构体  位域
        uint8_t base_h;
    }__attribute__((packed));
    SegmentDescriptor nullSegmentDescriptor;
    SegmentDescriptor unusedSegmentDescriptor;
    SegmentDescriptor codeSegmentDescriptor;
    SegmentDescriptor dataSegmentDescriptor;

    
    

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();

private:
    
};





#endif // !__GDT_H__      