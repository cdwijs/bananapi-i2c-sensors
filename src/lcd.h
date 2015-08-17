#ifndef LCD_H
#define LCD_H
#include "i2c.h" //is there a way to not include i2c.h here?
#include <QString>

class lcd
{
public:
    lcd();
    ~lcd();
    bool write(QString line, unsigned int position); //2 line display, so 0 or 1
    void initialize (void);
private:
    i2c_message myI2cMsg;
    i2c myI2c;
    char buffer[17];
};

#endif // LCD_H
