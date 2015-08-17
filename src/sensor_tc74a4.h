#ifndef SENSOR_TC74A4_H
#define SENSOR_TC74A4_H
#include "i2c.h" //is there a way to not include i2c.h here?



class sensor_TC74A4
{
public:
    sensor_TC74A4(char address);
    bool getTemperature(float * result);
    bool initialize(void);
private:
    i2c myI2c;
    i2c_message myMessage;
    char buffer[I2C_BUFFER_SIZE];
};

#endif // SENSOR_TC74A4_H
