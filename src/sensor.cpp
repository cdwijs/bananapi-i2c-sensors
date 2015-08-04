#include "sensor.h"
#include <QDebug>
#include "i2c.h"

i2c myI2c;


sensor::sensor(char address)
{
    qDebug()<< "sensor constructor, address: " << address;
    myMessage.address = address;
}

sensor::~sensor()
{
    qDebug()<< "sensor destructor";
}

bool sensor::getValue(void)
{
    //float result;
    qDebug()<< "sensor getValue, address: " << myMessage.address;
    myMessage.length = 2;
    myMessage.buffer = buffer;

    if (myI2c.write(myMessage))
    {
        myI2c.read(myMessage);
       // result=3.14; //put into pointed value or struct
        return true;
    }
    else
    {
        qDebug()<< "sensor getValue failed";
        return false;
    }
}

bool sensor::initialize(void)
{
     qDebug()<< "sensor initialize";
     if (myI2c.initialize())
     {
         return true;
     }
     else
     {
         return false;
     }

}
