#include "sensor.h"
#include <QDebug>
#include "i2c.h"

//driver for MICROCHIP  TC74A4-3.3VCTTR  IC, TEMPERATURE SENSOR
//farnell ordercode 1652471
//http://nl.farnell.com/microchip/tc74a4-3-3vcttr/ic-temperature-sensor/dp/1652471?ost=1652471
//address = 0x4C

//TC74 communication:
//write:
//Write Address, command, data
//read:
//Write address, command
//Read address, data

//command 0: RTR, read temperature
//command 1: RWCR, read/write configuration




i2c myI2c; //variables declared here are shared by all objects


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
    float result;
    //TC74A4-3.3VCTTR code
    myMessage.address = 0x4C;
    qDebug()<< "sensor getValue, address: " << myMessage.address;
    myMessage.length = 1;
    myMessage.buffer = buffer;
    buffer[0]= 0; //command = 0, read temp
    myI2c.write(myMessage);
    myMessage.length = 1;
    myMessage.buffer = buffer;
    buffer[0]= 0; //command = 0, read temp
    myI2c.read(myMessage); //buffer[0] should now hold the temperature
    qDebug("TC74A4 value: %d ^C", buffer[0]);
    //end TC74A4-3.3VCTTR code

    //MICROCHIP  MCP9800A0T-M/OT  SENSOR, THERMAL 12BIT, SOT-23A-5
    //farnell ordercode 1439485
    //http://nl.farnell.com/microchip/mcp9800a0t-m-ot/sensor-thermal-12bit-sot-23a-5/dp/1439485?ost=1439485
    //address 0x48
    //also works for MCP9801, 0x49
    //also works for TCN75A, 0x4A
    myMessage.address = 0x4A;
    myMessage.buffer = buffer;
    qDebug()<< "sensor getValue, address: " << myMessage.address;
    myMessage.length = 2;
    buffer[0]= 1; //pointer = 1, config
    buffer[1]= (1<<5 | 1<<6); //bit 5 and 6 high, adc resolution=12 bit (240msec)
    myI2c.write(myMessage);
    myMessage.length = 1;
    buffer[0]= 0; //pointer = 0, temperature
    myI2c.write(myMessage);
    myMessage.length = 2;
    myI2c.read(myMessage); //buffer [0] and buffer [1] now hold the temperature
    result =( buffer[0]<<8 ) + buffer[1]; //conversion must be checked for negative values
    result /=256;
    qDebug("MCP9800A0T value: %f ^C", result);
    //end TC74A4-3.3VCTTR code


    //NXP  SE95D,112  TEMPERATURE SENSOR, 3DEG CEL, SOIC-8
    //farnell ordercode 2396746
    //http://nl.farnell.com/nxp/se95d-112/temperature-sensor-3deg-cel-soic/dp/2396746?ost=SE95D%2C112
    //address 0x4F
    myMessage.address = 0x4F;
    myMessage.buffer = buffer;
    qDebug()<< "sensor getValue, address: " << myMessage.address;
    myMessage.length = 2;
    buffer[0]= 1; //pointer = 1, config
    buffer[1]= 0; //defaults values: 10 conv/s
    myI2c.write(myMessage);
    myMessage.length = 1;
    buffer[0]= 0; //pointer = 0, temperature
    myI2c.write(myMessage);
    myMessage.length = 2;
    myI2c.read(myMessage); //buffer [0] and buffer [1] now hold the temperature
    result =( buffer[0]<<8 ) + buffer[1]; //conversion must be checked for negative values
    result /=256;
    qDebug("SE95D value: %f ^C", result);
    //end SE95D code


    return true;
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
