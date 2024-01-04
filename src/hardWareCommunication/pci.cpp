#include "hardWareCommunication/pci.h"

PeripheralCommentInterconnectDeviceDescriptor::PeripheralCommentInterconnectDeviceDescriptor() {}
PeripheralCommentInterconnectDeviceDescriptor::~PeripheralCommentInterconnectDeviceDescriptor() {}

PeripheralCommentInterconnectControl::PeripheralCommentInterconnectControl()
    : dataPort(0xCFC),
      commandPort(0xCF8) // CONFIG_ADDRESS 的地址是 0xCF8，CONFIG_DATA 的地址是 0xCFC
{
}
PeripheralCommentInterconnectControl::~PeripheralCommentInterconnectControl() {}

uint32_t PeripheralCommentInterconnectControl::Read(uint8_t bus, uint8_t device, uint8_t function, uint8_t registerOffset)
{

    uint32_t address =
        1 << 31 |
        ((bus & 0xff) << 16) |
        ((device & 0x1f) << 11) |
        ((function & 0x07) << 8) |
        (registerOffset & 0xfc);
    commandPort.Write(address);
    uint32_t result = dataPort.Read();
    return result;
}
void PeripheralCommentInterconnectControl::Write(uint8_t bus, uint8_t device, uint8_t function, uint8_t registerOffset, uint32_t writeData)
{
    uint32_t id =
        1 << 31 |
        ((bus & 0xff) << 16) |
        ((device & 0x1f) << 11) |
        ((function & 0x07) << 8) |
        (registerOffset & 0xfc);
    commandPort.Write(id);
    dataPort.Write(writeData);
}
bool PeripheralCommentInterconnectControl::DeviceHasFunction(uint8_t bus, uint8_t device)
{
    return Read(bus, device, 0, 0x0e) & (1 << 7);
}

void PeripheralCommentInterconnectControl::SelectDriver(DriverManger *driverManger)
{
    for (uint16_t bus = 0; bus < 256; bus++)
    {
        for (uint8_t device = 0; device < 32; device++)
        {

            if (bus == 0 && device == 1)
            {
                printfHex(Read(bus, device, 0, 0));
                printf("\n");
            }

            int functionNumber = DeviceHasFunction((uint8_t)bus, device) ? 8 : 1;
            for (uint8_t function = 0; function < functionNumber; function++)
            {
                PeripheralCommentInterconnectDeviceDescriptor pciDev = GetDeviceDescriptor((uint8_t)bus, device, function);
                // printf(" functionNumber ");
                // // printfHex((pciDev.venderId & 0xff00) >> 8);
                // printfHex(functionNumber & 0xff);
                if (pciDev.venderId == 0 || pciDev.venderId == 0xffff)
                    continue;

                printf("PCI BUS ");
                printfHex(bus);

                printf(", DEVICE ");
                printfHex(device);

                printf(", FUNCTION ");
                printfHex(function);

                printf(" = VENDOR ");
                printfHex(pciDev.venderId);

                printf(", DEVICE ");
                printfHex(pciDev.deviceId);
                printf("\n");
            }
        }
    }
}
PeripheralCommentInterconnectDeviceDescriptor PeripheralCommentInterconnectControl::GetDeviceDescriptor(uint8_t bus, uint8_t device, uint8_t function)
{
    PeripheralCommentInterconnectDeviceDescriptor result;
    result.bus = bus;
    result.device = device;
    result.function = function;

    uint32_t temp = Read(bus, device, function, 0x00);
    result.venderId = temp;
    result.deviceId = (temp >> 16);

    temp = Read(bus, device, function, 0x04);

    result.revisionID = temp;
    result.progIF = (temp >> 8);
    result.subClass = (temp >> 16);
    result.classCode = (temp >> 24);

    result.interrupt = Read(bus, device, function, 0x3c);
    return result;
}
