#ifndef __AMD_AM79C973_H__
#define __AMD_AM79C973_H__
#include "common/print.h"
#include "common/types.h"
#include "hardWareCommunication/interrupts.h"
#include "hardWareCommunication/pci.h"
#include "hardWareCommunication/port.h"
class PeripheralCommentInterconnectDeviceDescriptor;

class amd_am79c973;

class RawDataHandler
{
  public:
    RawDataHandler(amd_am79c973 *backend);
    ~RawDataHandler();

    virtual bool OnRawDataReceived(uint8_t *buffer, uint32_t size);
    void Send(uint8_t *buffer, uint32_t size);

  protected:
    amd_am79c973 *backend;
};
class amd_am79c973 : public Driver, public InterruptHandler
{
  private:
    struct InitializationBlock
    {
        uint16_t mode;
        unsigned reserved1 : 4;
        unsigned numSendBuffers : 4;
        unsigned reserved2 : 4;
        unsigned numReceivedBuffers : 4;
        uint64_t physicalAddress : 48;
        uint16_t reserved3;
        uint64_t logicalAddress;
        uint32_t receivedBufferDescriptorAddress;
        uint32_t sendBufferDescriptorAddress;
    } __attribute__((packed));
    struct BufferDescriptor
    {
        uint32_t address;
        uint32_t flags;
        uint32_t flags2;
        uint32_t avail;
    } __attribute__((packed));
    Port16Bit MACAddress0Port;
    Port16Bit MACAddress2Port;
    Port16Bit MACAddress4Port;

    Port16Bit registerDataPort;
    Port16Bit registerAddressPort;
    Port16Bit resetPort;
    Port16Bit busControlRegisterDataPort;

    InitializationBlock initBlock;

    BufferDescriptor *sendBufferDesc;
    uint8_t sendBufferDescMemory[2048 + 15];
    uint8_t sendBuffers[2048 + 15][8];
    uint8_t currentSendBuffer;

    BufferDescriptor *receivedBufferDesc;
    uint8_t receivedBufferDescMemory[2048 + 15];
    uint8_t receivedBuffers[2048 + 15][8];
    uint8_t currentReceivedBuffer;

    RawDataHandler *handler;

  public:
    amd_am79c973(PeripheralCommentInterconnectDeviceDescriptor *dev, InterruptManger *interrupts);
    ~amd_am79c973();

    void Activate();
    void Deactivate();
    void Reset();
    uint32_t HandleInterrupt(uint32_t esp);

    void Send(uint8_t *buffer, int size);
    void SetHandler(RawDataHandler *handler);
    void Receive();
};
#endif // !__AMD_AM79C973_H__
