#include "sensor_hih6030.h"
#include <QDebug>


sensor_HIH6030::sensor_HIH6030(unsigned char address)
{
    qDebug("HIH6030 constructor, address: %x",address);
    myMessage.address = address;
    myMessage.buffer = buffer;
}

bool sensor_HIH6030::getTemperature(float * result)
{
    //HONEYWELL S&C  HIH6030-021-001  SENSOR, HUMIDITY, NO FILTER, 4.5%, 8SOIC
    //farnell ordercode 2356755
    //http://nl.farnell.com/honeywell-s-c/hih6030-021-001/sensor-humidity-no-filter-4-5/dp/2356755?ost=2356755
    //http://sensing.honeywell.com/product-page?pr_id=147516
    //http://sensing.honeywell.com/i2c-comms-humidicon-tn-009061-2-en-final-07jun12.pdf
    //address 0x27
    qDebug("sensor getTemperature, address: 0x%x", myMessage.address);
    myMessage.length = 0;
    myI2c.write(myMessage); //request a new measurement via a dummy write
    myQobject.thread()->msleep(50);//device should take 37msec for a conversion
    myMessage.length = 4;
    myI2c.read(myMessage); //buffer [0]MSB and buffer [1]LSB now hold the humidity
    unsigned short humidity = static_cast<signed short>(((buffer[0]&0x3F)<<8) + buffer[1]); //top 2 bits are status bits
    *result = ((humidity*100.0) / 16382.0);
    qDebug("HIH6030 humidity: %f", *result);
}

bool sensor_HIH6030::getHumidity(float * result)
{
    qDebug("sensor getHumidity, address: 0x%x", myMessage.address);
    myMessage.length = 0;
    myI2c.write(myMessage); //request a new measurement via a dummy write
    myQobject.thread()->msleep(50);//device should take 37msec for a conversion
    myMessage.length = 4;
    myI2c.read(myMessage); //buffer [0]MSB and buffer [1]LSB now hold the humidity
    unsigned short temperature = static_cast<signed short>((buffer[2]<<8) + ((buffer[3]&0xFC))); //bottom 2 bits don't care
    temperature /=4;
    *result = (((temperature * 165.0) / 16382.0) - 40.0);
    qDebug("HIH6030 temperature: %f", *result);
}

bool sensor_HIH6030::initialize(void)
{
    return true;
}
