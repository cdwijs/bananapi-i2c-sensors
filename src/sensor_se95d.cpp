#include "sensor_se95d.h"
#include <QDebug>

sensor_SE95D::sensor_SE95D(unsigned char address)
{
    qDebug("SE95D constructor, address: %x",address);
    myMessage.address = address;
    myMessage.buffer = buffer;
}

bool sensor_SE95D::getTemperature(float * result)
{
    //NXP  SE95D,112  TEMPERATURE SENSOR, 3DEG CEL, SOIC-8
    //farnell ordercode 2396746
    //http://nl.farnell.com/nxp/se95d-112/temperature-sensor-3deg-cel-soic/dp/2396746?ost=SE95D%2C112
    //address 0x4F
    //also works for LM75AD,   0x4B
    //also works for LM75BD,   0x4E
    //also works for PCT2075D, 0x28
    qDebug("sensor getValue, address: 0x%x", myMessage.address);
    myMessage.length = 1;
    buffer[0]= 0; //pointer = 0, temperature
    myI2c.write(myMessage);
    myMessage.length = 2;
    myI2c.read(myMessage); //buffer [0] and buffer [1] now hold the temperature
    *result = static_cast<signed short>(((buffer[0]<<8)+buffer[1]));
    *result /=256;
    qDebug("SE95D value: %f ^C", *result);
}

bool sensor_SE95D::initialize(void)
{
    qDebug("sensor initialize, address: 0x%x", myMessage.address);
    myMessage.length = 2;
    buffer[0]= 1; //pointer = 1, config
    buffer[1]= 0; //defaults values: 10 conv/s
    myI2c.write(myMessage);
}
