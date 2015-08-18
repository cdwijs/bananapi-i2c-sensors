#ifndef SENSOR_AT42QT1070_H
#define SENSOR_AT42QT1070_H
#include "i2c.h" //is there a way to not include i2c.h here?

class sensor_AT42QT1070
{
public:
    sensor_AT42QT1070(unsigned char address);
    bool getKeys(unsigned char * result);
    bool initialize(void);
private:
    i2c myI2c;
    i2c_message myMessage;
    char buffer[I2C_BUFFER_SIZE];
};

#endif // SENSOR_AT42QT1070_H
