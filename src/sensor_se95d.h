#ifndef SENSOR_SE95D_H
#define SENSOR_SE95D_H
#include "i2c.h" //is there a way to not include i2c.h here?

class sensor_SE95D
{
public:
    sensor_SE95D(unsigned char address);
    bool getTemperature(float * result);
    bool initialize(void);
private:
    i2c myI2c;
    i2c_message myMessage;
    char buffer[I2C_BUFFER_SIZE];
};

#endif // SENSOR_SE95D_H
