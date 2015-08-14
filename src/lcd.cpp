#include "lcd.h"
#include "i2c.h"
#include <QDebug>

const int LCD_LINELENGTH = 17;
const int LCD_INITLENGTH = 6;
const int LCD_LOCATIONLENGTH = 2;

// driver for BATRON  BTHQ21605V-COG-FSRE-I2C  LCD MODULE, ALPHANUMERIC, 2X16
// farnell ordercode 1220409 connected to con3 of the bananapi
// http://nl.farnell.com/batron/bthq21605v-cog-fsre-i2c/lcd-module-alphanumeric-2x16/dp/1220409?ost=1220409

lcd::lcd()
{
    qDebug()<< "lcd constructor";
    myI2cMsg.buffer = buffer;

    //Init i2c LCD
    myI2cMsg.address = 0x3B;
    myI2cMsg.buffer[0]=0x00;
    myI2cMsg.buffer[1]=0x25;
    myI2cMsg.buffer[2]=0x42;
    myI2cMsg.buffer[3]=0xA7;
    myI2cMsg.buffer[4]=0x24;
    myI2cMsg.buffer[5]=0x0C;
    myI2cMsg.length = LCD_INITLENGTH;
    myI2c.write(myI2cMsg);
}

lcd::~lcd()
{
    qDebug()<< "lcd destructor";
}

bool lcd::write(char line1[16], char line2[16])
{
    qDebug()<< "lcd write";
    qDebug()<< "lcd line 1: " << line1;
    myI2cMsg.address = 0x3B;
    myI2cMsg.buffer[0]=0x24;
    myI2cMsg.buffer[1]=0x80;
    myI2cMsg.length = LCD_LOCATIONLENGTH;
    myI2c.write(myI2cMsg);
    myI2cMsg.buffer[0]=0x40;
    myI2cMsg.buffer[1]=line1[0]|0x80;
    myI2cMsg.buffer[2]=line1[1]|0x80;
    myI2cMsg.buffer[3]=line1[2]|0x80;
    myI2cMsg.buffer[4]=line1[3]|0x80;
    myI2cMsg.buffer[5]=line1[4]|0x80;
    myI2cMsg.buffer[6]=line1[5]|0x80;
    myI2cMsg.buffer[7]=line1[6]|0x80;
    myI2cMsg.buffer[8]=line1[7]|0x80;
    myI2cMsg.buffer[9]=line1[8]|0x80;
    myI2cMsg.buffer[10]=line1[9]|0x80;
    myI2cMsg.buffer[11]=line1[10]|0x80;
    myI2cMsg.buffer[12]=line1[11]|0x80;
    myI2cMsg.buffer[13]=line1[12]|0x80;
    myI2cMsg.buffer[14]=line1[13]|0x80;
    myI2cMsg.buffer[15]=line1[14]|0x80;
    myI2cMsg.buffer[16]=line1[15]|0x80;
    myI2cMsg.length = LCD_LINELENGTH;
    myI2c.write(myI2cMsg);
    qDebug()<< "lcd line 2: " << line2;
    myI2cMsg.buffer[0]=0x24;
    myI2cMsg.buffer[1]=0x80|0x40;
    myI2cMsg.length = LCD_LOCATIONLENGTH;
    myI2c.write(myI2cMsg);
    myI2cMsg.buffer[0]=0x40;
    myI2cMsg.buffer[1]=line2[0]|0x80;
    myI2cMsg.buffer[2]=line2[1]|0x80;
    myI2cMsg.buffer[3]=line2[2]|0x80;
    myI2cMsg.buffer[4]=line2[3]|0x80;
    myI2cMsg.buffer[5]=line2[4]|0x80;
    myI2cMsg.buffer[6]=line2[5]|0x80;
    myI2cMsg.buffer[7]=line2[6]|0x80;
    myI2cMsg.buffer[8]=line2[7]|0x80;
    myI2cMsg.buffer[9]=line2[8]|0x80;
    myI2cMsg.buffer[10]=line2[9]|0x80;
    myI2cMsg.buffer[11]=line2[10]|0x80;
    myI2cMsg.buffer[12]=line2[11]|0x80;
    myI2cMsg.buffer[13]=line2[12]|0x80;
    myI2cMsg.buffer[14]=line2[13]|0x80;
    myI2cMsg.buffer[15]=line2[14]|0x80;
    myI2cMsg.buffer[16]=line2[15]|0x80;
    myI2cMsg.length = LCD_LINELENGTH;
    myI2c.write(myI2cMsg);
    return true; // should actually check if the i2c transactions are ok
}

void lcd::initialize (void)
{
    qDebug()<< "lcd initialize";


}
