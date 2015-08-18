#include "i2c.h"
#include <QDebug>
#include <QFile>

//https://learn.sparkfun.com/tutorials/programming-the-pcduino/i2c-communications
#include <stdlib.h>
#include <unistd.h>
#if defined(Q_OS_LINUX)
  #include <linux/i2c.h>
  #include <linux/i2c-dev.h>
  #include <sys/ioctl.h>
#endif
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

i2c::i2c()
{
    qDebug()<< "i2c constructor";
    #if defined(Q_OS_LINUX)
      // Create a file descriptor for the I2C bus
      i2cHandle = open("/dev/i2c-2", O_RDWR); //get adapter string from above routines
      qDebug("i2c handle: 0x%x",i2cHandle);
      opResult = ioctl(i2cHandle, I2C_TENBIT, 0); //device is 7 bit address
    #endif
}

i2c::~i2c()
{
    qDebug("i2c destructor, closing i2c handle: 0x%x",i2cHandle);
    #if defined(Q_OS_LINUX)
      close(i2cHandle);
    #endif
}

bool i2c::read(i2c_message msg) //return true for success, false for failure
{
    #if defined(Q_OS_LINUX)
     //   qDebug()<< "i2c read: Address: " << msg.address << "lenth: " << msg.length;
        opResult = ioctl(i2cHandle, I2C_SLAVE, msg.address);
        opResult = ::read(i2cHandle, msg.buffer, msg.length);
     //   qDebug()<< opResult << " bytes read";
      //  myQobject.thread()->msleep(200);//emulate slow read
     //   qDebug()<< "i2c read done";
    #endif
    return true; //add check to see if the requested amount is read
}

bool i2c::write(i2c_message msg)
{
    #if defined(Q_OS_LINUX)
    //    qDebug()<< "i2c write: Address: " << msg.address << "lenth: " << msg.length;
        // Tell the I2C peripheral what the address of the device is.
        opResult = ioctl(i2cHandle, I2C_SLAVE, msg.address);

        opResult = ::write(i2cHandle, msg.buffer, msg.length);
      //  qDebug()<< opResult << " bytes written";

       // myQobject.thread()->msleep(200);//emulate slow write
    //    qDebug()<< "i2c write done";
    #endif
    return true; //add check to see if the requested amount is written
}

bool i2c::initialize() //need adapter number
{
    qDebug()<< "i2c initialize";
    return true;
}
