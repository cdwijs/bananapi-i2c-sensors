#ifndef I2C_H
#define I2C_H

const char I2C_BUFFER_SIZE=57; //AT42QT1070-SSU needs 57, display needs 17

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
private:
    int opResult;   // for error checking of operations
    int i2cHandle;
};

#endif // I2C_H
