#ifndef __DRIVER_H__
#define __DRIVER_H__
#include "types.h"

class Driver
{

public:
    Driver();
    ~Driver();

    virtual void Activate()=0;
    virtual void Reset()=0;
    virtual void Deactivate()=0;
};
class DriverManger
{
public:
    DriverManger();
    ~DriverManger();
    void AddDriver(Driver *driver);
    void ActivateAll();
protected:
    Driver * drivers[256];
    int numDrivers;
};



#endif // !__DRIVER_H__