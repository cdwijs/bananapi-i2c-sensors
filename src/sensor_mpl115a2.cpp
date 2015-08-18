#include "sensor_mpl115a2.h"
#include <QDebug>

sensor_MPL115A2::sensor_MPL115A2(unsigned char address)
{
    qDebug("MPL115A2 constructor, address: %x",address);
    myMessage.address = address;
    myMessage.buffer = buffer;
}

bool sensor_MPL115A2::getPressure(float * result)
{
    //FREESCALE SEMICONDUCTOR  MPL115A2  MINI I2C DIGITAL BAROMETER, 50 TO 115KPa
    //farnell ordercode 2102577
    //http://nl.farnell.com/freescale-semiconductor/mpl115a2/mini-i2c-digital-barometer-50/dp/2102577?ost=2102577
    //http://www.farnell.com/datasheets/1789292.pdf
    //address 0x60
    qDebug("sensor getPressure, address: 0x%x", myMessage.address);
    myMessage.length = 2;
    buffer[0]= 0x12; //pointer=0x12, CONVERT
    buffer[1]= 0;
    myI2c.write(myMessage); //start conversion
    myQobject.thread()->msleep(4);//device should take 3msec for a conversion
    myMessage.length = 1;
    buffer[0]= 0; //pointer=0, ADC values
    myI2c.write(myMessage);
    myMessage.length = 4;
    myI2c.read(myMessage); //buffer 0..3 now hold the ADC values for pressure and temp
    float Tadc = ((buffer[0]<<8)+buffer[1]);
    Tadc /= 64; //2^6
    float Padc = ((buffer[2]<<8)+buffer[3]);
    Padc /= 64; //2^6
    //calculate pressure:
    float c12x2 = c12Coefficient * Tadc;
    float a1 = b1Coefficient + c12x2;
    float a1x1 = a1 * Padc;
    float y1 = a0Coefficient + a1x1;
    float a2x2 = b2Coefficient * Tadc;
    float pcomp = y1 + a2x2;
    *result = (((115.0 - 50.0)/1023)*pcomp + 50.0);
    qDebug("MPL115A2 pressure: %f KPa", *result);
}

bool sensor_MPL115A2::initialize(void)
{
    qDebug("sensor initialize, address: 0x%x", myMessage.address);
    //first get correction factors (Coefficients, need only once be collected)
    myMessage.length = 1;
    buffer[0]= 4; //pointer=4, a0 coefficient MSB
    myI2c.write(myMessage);
    myMessage.length = 8;
    myI2c.read(myMessage); //buffer 0..7 now hold the coefficients
    a0Coefficient = static_cast<signed short>(((buffer[0]<<8)+buffer[1]));//int cast needed for negative
    a0Coefficient /= 8; //2^3
    b1Coefficient = static_cast<signed short>(((buffer[2]<<8)+buffer[3]));
    b1Coefficient /= 8192; //2^13
    b2Coefficient = static_cast<signed short>(((buffer[4]<<8)+buffer[5]));
    b2Coefficient /= 16384; //2^14
    c12Coefficient = static_cast<signed short>(((buffer[6]<<8)+buffer[7]));
    c12Coefficient /= 16777216; //2^24
}
