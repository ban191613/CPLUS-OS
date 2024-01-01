#include "drivers/driver.h"
Driver::Driver()
{

}
Driver::~Driver()
{

}


DriverManger::DriverManger()
:numDrivers(0)
{

}
DriverManger::~DriverManger()
{

}
void DriverManger::AddDriver(Driver *driver)
{
    drivers[numDrivers++]=driver;
}
void DriverManger::ActivateAll()
{
    for (uint8_t i = 0; i < numDrivers; i++)
    {
        drivers[i]->Activate();
    }
    
}