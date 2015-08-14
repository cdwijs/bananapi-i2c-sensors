#include "sensor.h"
#include <QDebug>
#include "i2c.h"
#include <QThread> //for msleep

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
QObject myQobject;

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
    myMessage.address = 0x48;
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
    //also works for LM75AD,   0x4B
    //also works for LM75BD,   0x4E
    //also works for PCT2075D, 0x28
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



    //MICROCHIP  EMC1001-AFZQ-TR  IC, TEMP SENSOR, +/- 1.5 DEG, SOT23-6
    //farnell ordercode 2361928
    //http://nl.farnell.com/microchip/emc1001-afzq-tr/ic-temp-sensor--1-5-deg-sot23/dp/2361928?ost=2361928
    //address 0x38
    myMessage.address = 0x38;
    myMessage.buffer = buffer;
    qDebug()<< "sensor getValue, address: " << myMessage.address;
    myMessage.length = 2;
    buffer[0]= 3; //pointer = 3, config
    buffer[1]= 0; //defaults values: 10 conv/s
    myI2c.write(myMessage);
    myMessage.length = 1;
    buffer[0]= 0; //pointer = 0, temperature
    myI2c.write(myMessage);
    myMessage.length = 3;
    myI2c.read(myMessage); //buffer [0] and buffer [2] now hold the temperature
    result =( buffer[0]<<8 ) + buffer[2]; //conversion must be checked for negative values
    result /=256;
    qDebug("EMC1001 value: %f ^C", result);
    //end EMC1001 code


    //HONEYWELL S&C  HIH6030-021-001  SENSOR, HUMIDITY, NO FILTER, 4.5%, 8SOIC
    //farnell ordercode 2356755
    //http://nl.farnell.com/honeywell-s-c/hih6030-021-001/sensor-humidity-no-filter-4-5/dp/2356755?ost=2356755
    //http://sensing.honeywell.com/product-page?pr_id=147516
    //http://sensing.honeywell.com/i2c-comms-humidicon-tn-009061-2-en-final-07jun12.pdf
    //address 0x27
    myMessage.address = 0x27;
    myMessage.buffer = buffer;
    qDebug()<< "sensor getValue, address: " << myMessage.address;
    myMessage.length = 0;
    myI2c.write(myMessage); //request a new measurement via a dummy write
    myQobject.thread()->msleep(50);//device should take 37msec for a conversion
    myMessage.length = 4;
    myI2c.read(myMessage); //buffer [0]MSB and buffer [1]LSB now hold the temperature
    unsigned short humidity = ( (buffer[0]&0x3F)<<8 ) + buffer[1]; //top 2 bits are status bits
    result = ((humidity*100.0) / 16382.0);
    qDebug("HIH6030 humidity: %f", result);
    unsigned short temperature = (buffer[2]<<8) + ((buffer[3]&0xFC)); //bottom 2 bits don't care
    temperature /=4;
    result = (((temperature * 165.0) / 16382.0) - 40.0);
    qDebug("HIH6030 temperature: %f", result);
    //end HIH6030

    //FREESCALE SEMICONDUCTOR  MPL115A2  MINI I2C DIGITAL BAROMETER, 50 TO 115KPa
    //farnell ordercode 2102577
    //http://nl.farnell.com/freescale-semiconductor/mpl115a2/mini-i2c-digital-barometer-50/dp/2102577?ost=2102577
    //http://www.farnell.com/datasheets/1789292.pdf
    //address 0x60
    myMessage.address = 0x60;
    myMessage.buffer = buffer;
    qDebug()<< "sensor getValue, address: " << myMessage.address;
    //first get correction factors (Coefficients, need only once be collected)
    myMessage.length = 1;
    buffer[0]= 4; //pointer=4, a0 coefficient MSB
    myI2c.write(myMessage);
    myMessage.length = 8;
    myI2c.read(myMessage); //buffer 0..7 now hold the coefficients
    float a0Coefficient = static_cast<signed short>(((buffer[0]<<8)+buffer[1]));//int cast needed for negative
    a0Coefficient /= 8; //2^3
    float b1Coefficient = static_cast<signed short>(((buffer[2]<<8)+buffer[3]));
    b1Coefficient /= 8192; //2^13
    float b2Coefficient = static_cast<signed short>(((buffer[4]<<8)+buffer[5]));
    b2Coefficient /= 16384; //2^14
    float c12Coefficient = static_cast<signed short>(((buffer[6]<<8)+buffer[7]));
    c12Coefficient /= 16777216; //2^24
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
    result = (((115.0 - 50.0)/1023)*pcomp + 50.0);
    qDebug("MPL115A2 pressure: %f KPa", result);
    //end HIH6030
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
