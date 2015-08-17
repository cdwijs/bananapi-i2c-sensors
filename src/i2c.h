#ifndef I2C_H
#define I2C_H

const char I2C_BUFFER_SIZE=40;

struct i2c_message
{
    int length;
    char * buffer;
    int address;
};


class i2c
{
public:
    i2c();
    ~i2c();
    bool read(i2c_message msg); //need address, data, length, return true for success, false for failure
    bool write(i2c_message msg); //need address, data, length
    bool initialize(void); //need adapter number
};

#endif // I2C_H
