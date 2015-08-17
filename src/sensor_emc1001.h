#ifndef SENSOR_EMC1001_H
#define SENSOR_EMC1001_H
#include "i2c.h" //is there a way to not include i2c.h here?

class sensor_EMC1001
{
public:
    sensor_EMC1001(unsigned char address);
    bool getTemperature(float * result);
    bool initialize(void);
private:
    i2c myI2c;
    i2c_message myMessage;
    char buffer[I2C_BUFFER_SIZE];
};

#endif // SENSOR_EMC1001_H
