#include "sensor_tc74a4.h"
#include <QDebug>

sensor_TC74A4::sensor_TC74A4(char address)
{
    qDebug("TC74A4 constructor, address: %x",address);
    myMessage.address = address;
    myMessage.buffer = buffer;
}


bool sensor_TC74A4::getTemperature(float * result)
{
    //driver for MICROCHIP  TC74A4-3.3VCTTR  IC, TEMPERATURE SENSOR
    //farnell ordercode 1652471
    //http://nl.farnell.com/microchip/tc74a4-3-3vcttr/ic-temperature-sensor/dp/1652471?ost=1652471
    //address = 0x4C
    qDebug("sensor getValue, address: 0x%x", myMessage.address);
    myMessage.length = 1;
    buffer[0]= 0; //command = 0, read temp
    myI2c.write(myMessage);
    myMessage.length = 1;
    myMessage.buffer = buffer;
    buffer[0]= 0; //command = 0, read temp
    myI2c.read(myMessage); //buffer[0] should now hold the temperature
    qDebug("TC74A4 value: %d ^C", buffer[0]);
    *result = static_cast<signed char>(buffer[0]); //test with negative temp
    return true; //check for correct i2c communication instead of blindly return true
}

bool sensor_TC74A4::initialize(void)
{
    qDebug("sensor initialize, address: 0x%x", myMessage.address);
    //standard configuration is OK for this sensor
    return true;
}
