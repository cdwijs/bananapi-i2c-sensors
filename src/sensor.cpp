#include "sensor.h"
#include <QDebug>
#include "i2c.h"

i2c myI2c;

sensor::sensor()
{
    qDebug()<< "sensor constructor";
}

sensor::~sensor()
{
    qDebug()<< "sensor destructor";
}

bool sensor::getValue(void)
{
    float result;
    qDebug()<< "sensor getValue";
    if (myI2c.write())
    {
        myI2c.read();
        result=3.14; //put into pointed value or struct
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
     myI2c.initialize();
}
