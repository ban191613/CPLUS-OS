#ifndef __DRIVER_H__
#define __DRIVER_H__
#include "common/types.h"

class Driver
{

  public:
    Driver();

    ~Driver(); // C++  linker文件无法设置虚函数，会报错
    virtual void Activate() = 0;
    virtual void Reset() = 0;
    virtual void Deactivate() = 0;
};
class DriverManger
{
  public:
    DriverManger();
    ~DriverManger();
    void AddDriver(Driver *driver);
    void ActivateAll();
    Driver *drivers[256];

  protected:
    int numDrivers;
};

#endif // !__DRIVER_H__