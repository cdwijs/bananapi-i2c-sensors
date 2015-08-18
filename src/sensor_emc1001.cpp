#include "sensor_emc1001.h"
#include <QDebug>

sensor_EMC1001::sensor_EMC1001(unsigned char address)
{
    qDebug("EMC1001 constructor, address: %x",address);
    myMessage.address = address;
    myMessage.buffer = buffer;
}

bool sensor_EMC1001::getTemperature(float * result)
{
    //MICROCHIP  EMC1001-AFZQ-TR  IC, TEMP SENSOR, +/- 1.5 DEG, SOT23-6
    //farnell ordercode 2361928
    //http://nl.farnell.com/microchip/emc1001-afzq-tr/ic-temp-sensor--1-5-deg-sot23/dp/2361928?ost=2361928
    //address 0x38
    qDebug("sensor getTemperature, address: 0x%x", myMessage.address);
    myMessage.length = 1;
    buffer[0]= 0; //pointer = 0, temperature
    myI2c.write(myMessage);
    myMessage.length = 3;
    myI2c.read(myMessage); //buffer [0] and buffer [2] now hold the temperature
    *result = static_cast<signed short>(((buffer[0]<<8)+buffer[2]));
    *result /=256;
    qDebug("EMC1001 value: %f ^C", *result);
}

bool sensor_EMC1001::initialize(void)
{
    qDebug("sensor initialize, address: 0x%x", myMessage.address);
    myMessage.length = 2;
    buffer[0]= 3; //pointer = 3, config
    buffer[1]= 0; //defaults values: 10 conv/s
    myI2c.write(myMessage);
}
