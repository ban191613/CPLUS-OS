#ifndef __PCI_H__
#define __PCI_H__
#include "hardWareCommunication/port.h"
#include "common/types.h"
#include "hardWareCommunication/interrupts.h"
#include "drivers/driver.h"
#include "common/print.h"
class PeripheralCommentInterconnectDeviceDescriptor;
class PeripheralCommentInterconnectControl
{

public:
    PeripheralCommentInterconnectControl();
    ~PeripheralCommentInterconnectControl();

    uint32_t Read(uint8_t bus, uint8_t device, uint8_t fuction, uint8_t registerOffset);
    void Write(uint8_t bus, uint8_t device, uint8_t fuction, uint8_t registerOffset, uint32_t write);

    bool DeviceHasFunction(uint8_t bus, uint8_t device);

    void SelectDriver(DriverManger *driverManger);
    PeripheralCommentInterconnectDeviceDescriptor GetDeviceDescriptor(uint8_t bus, uint8_t device, uint8_t function);

protected:
    Port32Bit dataPort;
    Port32Bit commandPort;
};
class PeripheralCommentInterconnectDeviceDescriptor
{

public:
    void friend PeripheralCommentInterconnectControl::SelectDriver(DriverManger *driverManger);
    PeripheralCommentInterconnectDeviceDescriptor friend PeripheralCommentInterconnectControl::GetDeviceDescriptor(uint8_t bus, uint8_t device, uint8_t function);
    PeripheralCommentInterconnectDeviceDescriptor();
    ~PeripheralCommentInterconnectDeviceDescriptor();

private:
    uint32_t portBase;
    uint32_t interrupt;

    uint8_t bus;
    uint8_t device;
    uint8_t function;

    uint16_t deviceId;
    uint16_t venderId;

    uint8_t classCode;
    uint8_t subClass;
    uint8_t progIF;
    uint8_t revisionID;
};

#endif // !__PCI_H__