#ifndef __DRIVER_H__
#define __DRIVER_H__
class Driver
{

public:
    Driver();
    ~Driver();

    virtual void Activate();
    virtual void Reset();
    virtual void Deactivate();
};
class DriverManger
{
public:
    void AddDriver(Driver *driver);
protected:
    Driver * drivers[256];
    int numDrivers;
};



#endif // !__DRIVER_H__