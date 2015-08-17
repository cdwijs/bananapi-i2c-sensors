#ifndef SENSOR_MCP9800A0_H
#define SENSOR_MCP9800A0_H
#include "i2c.h" //is there a way to not include i2c.h here?

class sensor_MCP9800A0
{
public:
    sensor_MCP9800A0(unsigned char address);
    bool getTemperature(float * result);
    bool initialize(void);
private:
    i2c myI2c;
    i2c_message myMessage;
    char buffer[I2C_BUFFER_SIZE];
};

#endif // SENSOR_MCP9800A0_H
