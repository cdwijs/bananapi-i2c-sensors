#ifndef SENSOR_HIH6030_H
#define SENSOR_HIH6030_H
#include "i2c.h" //is there a way to not include i2c.h here?
#include <QThread> //for msleep

class sensor_HIH6030
{
public:
    sensor_HIH6030(unsigned char address);
    bool getTemperature(float * result);
    bool getHumidity(float * result);
    bool initialize(void);
private:
    i2c myI2c;
    i2c_message myMessage;
    char buffer[I2C_BUFFER_SIZE];
    QObject myQobject; //for msleep
};

#endif // SENSOR_HIH6030_H
