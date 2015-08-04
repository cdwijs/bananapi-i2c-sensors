#ifndef SENSOR_H
#define SENSOR_H


class sensor
{
public:
    sensor();
    ~sensor();
    bool getValue(void); //add pointer to some struct or value
    bool initialize(void);
};

#endif // SENSOR_H
