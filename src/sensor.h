#ifndef SENSOR_H
#define SENSOR_H
#include "i2c.h" //is there a way to not include i2c.h here?

class sensor
{
public:
    sensor(char address);
    ~sensor();
    bool getValue(void); //add pointer to some struct or value
    bool initialize(void);
private:
    i2c_message myMessage;
    char buffer[40];
};

#endif // SENSOR_H
