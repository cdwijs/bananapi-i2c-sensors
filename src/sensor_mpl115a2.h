#ifndef SENSOR_MPL115A2_H
#define SENSOR_MPL115A2_H
#include "i2c.h" //is there a way to not include i2c.h here?
#include <QThread> //for msleep

class sensor_MPL115A2
{
public:
    sensor_MPL115A2(unsigned char address);
    bool getPressure(float * result);
    bool initialize(void);
private:
    i2c myI2c;
    i2c_message myMessage;
    char buffer[I2C_BUFFER_SIZE];
    float a0Coefficient;
    float b1Coefficient;
    float b2Coefficient;
    float c12Coefficient;
    QObject myQobject; //for msleep
};

#endif // SENSOR_MPL115A2_H
