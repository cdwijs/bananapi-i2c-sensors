#include "i2c.h"
#include <QDebug>

QObject myQobject;

#include <QThread> //for msleep, to emulate (very) slow i2c communication

i2c::i2c()
{
    qDebug()<< "i2c constructor";
}

i2c::~i2c()
{
    qDebug()<< "i2c destructor";
}

bool i2c::read() //need address, data, length, return true for success, false for failure
{
    qDebug()<< "i2c read";
    myQobject.thread()->msleep(500);//emulate slow read
    qDebug()<< "i2c read done";
    return true;
}

bool i2c::write() //need address, data, length
{
   qDebug()<< "i2c write";
   myQobject.thread()->msleep(500);//emulate slow read
   qDebug()<< "i2c write done";
   return true;
}

bool i2c::initialize() //need adapter number
{
    qDebug()<< "i2c initialize";
    return true;
}
