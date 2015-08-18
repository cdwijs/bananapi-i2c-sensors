#include "sensor_at42qt1070.h"
#include <QDebug>

sensor_AT42QT1070::sensor_AT42QT1070(unsigned char address)
{
    qDebug("AT42QT1070 constructor, address: %x",address);
    myMessage.address = address;
    myMessage.buffer = buffer;
}

bool sensor_AT42QT1070::getKeys(unsigned char * result)
{
    //ATMEL  AT42QT1070-SSU  SENSOR, QTOUCH, 7-KEY, 14SOIC
    //farnell ordercode 1972020
    //http://nl.farnell.com/atmel/at42qt1070-ssu/sensor-qtouch-7-key-14soic/dp/1972020
    //address 0x1B
    qDebug("sensor getKeys, address: 0x%x", myMessage.address);
    myMessage.length = 1;
    buffer[0]=3; //3=Key Status
    myI2c.write(myMessage);
    myMessage.length = 1;
    myI2c.read(myMessage); //now buffer[0] holds the keys
    *result = buffer[0];
    qDebug("Keys: 0x%x",*result);
}

bool sensor_AT42QT1070::initialize(void)
{
    qDebug("sensor initialize, address: 0x%x", myMessage.address);
    myMessage.length = 2;
    buffer[0]=53; //53=guard channel, > 6 to disable guard key feature
    buffer[1]=7;
    myI2c.write(myMessage);
}
