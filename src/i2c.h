#ifndef I2C_H
#define I2C_H


//define a struct with address, data, length

class i2c
{
public:
    i2c();
    ~i2c();
    bool read(void); //need address, data, length, return true for success, false for failure
    bool write(void); //need address, data, length
    bool initialize(void); //need adapter number
};

#endif // I2C_H
