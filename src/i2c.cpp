#include "i2c.h"
#include <QDebug>
#include <QFile>

//https://learn.sparkfun.com/tutorials/programming-the-pcduino/i2c-communications
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

// Set up some variables that we'll use along the way
  int xlAddress = 0x53;   // accelerometer device address
  int tenBitAddress = 0;  // is the device's address 10-bit? Usually not.
  int opResult = 0;   // for error checking of operations
  int i2cHandle = 0;

//QObject myQobject;

//#include <QThread> //for msleep, to emulate (very) slow i2c communication

i2c::i2c()
{
 /*   QString filename="/dev/i2c-2";
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite) )
    {
        //QTextStream stream( &file );
        //stream << "something" << endl;
        qDebug()<< "i2c dev open";
    }


    file.close();
    qDebug()<< "i2c dev closed";*/




    qDebug()<< "i2c constructor";
    // Create a file descriptor for the I2C bus
    i2cHandle = open("/dev/i2c-2", O_RDWR);

    // Tell the I2C peripheral that the device address is (or isn't) a 10-bit
    //   value. Most probably won't be.
    opResult = ioctl(i2cHandle, I2C_TENBIT, tenBitAddress);


}

i2c::~i2c()
{
    qDebug()<< "i2c destructor";
    //close the file handle here
}

bool i2c::read(i2c_message msg) //return true for success, false for failure
{
 //   qDebug()<< "i2c read: Address: " << msg.address << "lenth: " << msg.length;
    opResult = ioctl(i2cHandle, I2C_SLAVE, msg.address);
    opResult = ::read(i2cHandle, msg.buffer, msg.length);
 //   qDebug()<< opResult << " bytes read";
  //  myQobject.thread()->msleep(200);//emulate slow read
 //   qDebug()<< "i2c read done";
    return true; //add check to see if the requested amount is read
}

bool i2c::write(i2c_message msg)
{
//    qDebug()<< "i2c write: Address: " << msg.address << "lenth: " << msg.length;
    // Tell the I2C peripheral what the address of the device is.
    opResult = ioctl(i2cHandle, I2C_SLAVE, msg.address);

    opResult = ::write(i2cHandle, msg.buffer, msg.length);
  //  qDebug()<< opResult << " bytes written";

   // myQobject.thread()->msleep(200);//emulate slow write
//    qDebug()<< "i2c write done";
    return true; //add check to see if the requested amount is written
}

bool i2c::initialize() //need adapter number
{
    qDebug()<< "i2c initialize";
    return true;
}
