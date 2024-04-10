#include "hardWareCommunication/pci.h"

PeripheralCommentInterconnectDeviceDescriptor::PeripheralCommentInterconnectDeviceDescriptor()
{
}
PeripheralCommentInterconnectDeviceDescriptor::~PeripheralCommentInterconnectDeviceDescriptor()
{
}

PeripheralCommentInterconnectControl::PeripheralCommentInterconnectControl()
    : dataPort(0xCFC), commandPort(0xCF8) // CONFIG_ADDRESS 的地址是 0xCF8，CONFIG_DATA 的地址是 0xCFC
{
}
PeripheralCommentInterconnectControl::~PeripheralCommentInterconnectControl()
{
}

uint32_t PeripheralCommentInterconnectControl::Read(uint8_t bus, uint8_t device, uint8_t function,
                                                    uint8_t registerOffset)
{

    uint32_t address =
        1 << 31 | ((bus & 0xff) << 16) | ((device & 0x1f) << 11) | ((function & 0x07) << 8) | (registerOffset & 0xfc);
    commandPort.Write(address);
    uint32_t result = dataPort.Read();
    return result;
}
void PeripheralCommentInterconnectControl::Write(uint8_t bus, uint8_t device, uint8_t function, uint8_t registerOffset,
                                                 uint32_t writeData)
{
    uint32_t id =
        1 << 31 | ((bus & 0xff) << 16) | ((device & 0x1f) << 11) | ((function & 0x07) << 8) | (registerOffset & 0xfc);
    commandPort.Write(id);
    dataPort.Write(writeData);
}
bool PeripheralCommentInterconnectControl::DeviceHasFunction(uint8_t bus, uint8_t device)
{
    return Read(bus, device, 0, 0x0c) & (1 << 23);
}

void PeripheralCommentInterconnectControl::SelectDriver(DriverManger *driverManger, InterruptManger *interruptManger)
{
    for (uint16_t bus = 0; bus < 256; bus++)
    {
        for (uint8_t device = 0; device < 32; device++)
        {

            int functionNumber = DeviceHasFunction((uint8_t)bus, device) ? 8 : 1;

            for (uint8_t function = 0; function < functionNumber; function++)
            {
                PeripheralCommentInterconnectDeviceDescriptor pciDev =
                    GetDeviceDescriptor((uint8_t)bus, device, function);
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

                printf(", CLASS ");
                printfHex(pciDev.classCode);

                printf(", SUBCLASS ");
                printfHex(pciDev.subClass);

                printf("\n");
                for (uint8_t barNumber = 0; barNumber < 6; barNumber++)
                {
                    BassAddressRegister bar = GetBaseAddressResister(bus, device, function, barNumber);
                    if (bar.address && (bar.type == InputOutput))
                    {
                        pciDev.portBase = (uint32_t)bar.address;
                    }
                }
                Driver *driver = GetDriver(pciDev, interruptManger);
                if (driver != nullptr)
                {
                    driverManger->AddDriver(driver);
                }
            }
        }
    }
}
PeripheralCommentInterconnectDeviceDescriptor PeripheralCommentInterconnectControl::GetDeviceDescriptor(
    uint8_t bus, uint8_t device, uint8_t function)
{
    PeripheralCommentInterconnectDeviceDescriptor result;
    result.bus = bus;
    result.device = device;
    result.function = function;

    uint32_t temp = Read(bus, device, function, 0x00);
    result.venderId = temp;
    result.deviceId = (temp >> 16);

    temp = Read(bus, device, function, 0x08);

    result.revisionID = temp;
    result.progIF = (temp >> 8);
    result.subClass = (temp >> 16);
    result.classCode = (temp >> 24);

    result.interrupt = Read(bus, device, function, 0x3c);
    return result;
}
Driver *PeripheralCommentInterconnectControl::GetDriver(PeripheralCommentInterconnectDeviceDescriptor dev,
                                                        InterruptManger *interruptManger)
{
    Driver *driver = nullptr;
    switch (dev.venderId)
    {
    case 0x1022:
        switch (dev.deviceId)
        {
        case 0x2000:
            driver = (amd_am79c973 *)MemoryManger::activeMemoryManger->malloc(sizeof(amd_am79c973));
            if (driver != 0)
                new (driver) amd_am79c973(&dev, interruptManger);
            else
                printf("AMD am79c973 instantiation failed\n");
            printf("AMD_am79c973 \n");
            return driver;
            break;
        }
        break;

    case 0x8086:
        break;
    }
    switch (dev.classCode)
    {
    case 0x03:
        switch (dev.subClass)
        {
        case 0x00: // VGA
            printf("VGA \n");
            break;
        }
        break;
    }
    return 0;
}

BassAddressRegister PeripheralCommentInterconnectControl::GetBaseAddressResister(uint16_t bus, uint8_t device,
                                                                                 uint8_t function, uint8_t bar)
{
    BassAddressRegister result;
    uint8_t harderType = Read(bus, device, function, 0x0c) & ((0x7f) << 16);
    int maxBars = 6 - 4 * (harderType);
    if (bar >= maxBars)
        return result;

    uint32_t bar_value = Read(bus, device, function, 0x10 + bar * 4);
    result.type = (bar_value & 1) ? InputOutput : MemoryMapping;
    if (result.type == MemoryMapping)
    {
        switch ((bar_value >> 1) & (0x3))
        {
        case 0: // 32bits
            break;
        case 1: // 20bits
            break;
        case 2: // 64bits
            break;
        }
    }
    else
    {
        result.address = (uint8_t *)(bar_value & ~0x3);
        result.prefectAble = false;
    }

    return result;
}