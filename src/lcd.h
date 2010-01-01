#ifndef LCD_H
#define LCD_H
#include "i2c.h" //is there a way to not include i2c.h here?

class lcd
{
public:
    lcd();
    ~lcd();
    bool write(char line1[16], char line2[16]);
    void initialize (void);
private:
    i2c_message myI2cMsg;
    i2c myI2c;
    char buffer[17];
};

#endif // LCD_H
