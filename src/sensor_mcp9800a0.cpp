#include "sensor_mcp9800a0.h"
#include <QDebug>

sensor_MCP9800A0::sensor_MCP9800A0(unsigned char address)
{
    qDebug("MCP9800A0 constructor, address: %x",address);
    myMessage.address = address;
}

bool sensor_MCP9800A0::getTemperature(float * result)
{
    //MICROCHIP  MCP9800A0T-M/OT  SENSOR, THERMAL 12BIT, SOT-23A-5
    //farnell ordercode 1439485
    //http://nl.farnell.com/microchip/mcp9800a0t-m-ot/sensor-thermal-12bit-sot-23a-5/dp/1439485?ost=1439485
    //address 0x48
    //also works for MCP9801, 0x49
    //also works for TCN75A, 0x4A
    myMessage.buffer = buffer;
    qDebug("sensor getValue, address: 0x%x", myMessage.address);
    myMessage.length = 1;
    buffer[0]= 0; //pointer = 0, temperature
    myI2c.write(myMessage);
    myMessage.length = 2;
    myI2c.read(myMessage); //buffer [0] and buffer [1] now hold the temperature
    *result = static_cast<signed short>(((buffer[0]<<8)+buffer[1]));
    *result /=256;
    qDebug("MCP9800A0T value: %f ^C", *result);
}

bool sensor_MCP9800A0::initialize(void)
{
    qDebug("sensor initialize, address: 0x%x", myMessage.address);
    myMessage.buffer = buffer;
    myMessage.length = 2;
    buffer[0]= 1; //pointer = 1, config
    buffer[1]= (1<<5 | 1<<6); //bit 5 and 6 high, adc resolution=12 bit (240msec)
    myI2c.write(myMessage);
}
