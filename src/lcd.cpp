#include "lcd.h"
#include "i2c.h"
#include <QDebug>

const int LCD_LINELENGTH = 17;
const int LCD_INITLENGTH = 6;
const int LCD_LOCATIONLENGTH = 2;

// driver for BATRON  BTHQ21605V-COG-FSRE-I2C  LCD MODULE, ALPHANUMERIC, 2X16
// farnell ordercode 1220409 connected to con3 of the bananapi
// http://nl.farnell.com/batron/bthq21605v-cog-fsre-i2c/lcd-module-alphanumeric-2x16/dp/1220409?ost=1220409

QByteArray myArray;

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

bool lcd::write(QString line, unsigned int position)
{
    qDebug("LCD write line %d",position);
    myI2cMsg.address = 0x3B;
    myI2cMsg.buffer[0]=0x24;
    if (position == 0) //2 line display
    {
        myI2cMsg.buffer[1]=0x80;
    }
    else
    {
        myI2cMsg.buffer[1]=0x80 | 0x40;
    }
    myI2cMsg.length = LCD_LOCATIONLENGTH;
    myI2c.write(myI2cMsg);

    myArray = line.toLocal8Bit();
    myI2cMsg.buffer[0]=0x40;
    myI2cMsg.buffer[1]=myArray[0]|0x80;
    myI2cMsg.buffer[2]=myArray[1]|0x80;
    myI2cMsg.buffer[3]=myArray[2]|0x80;
    myI2cMsg.buffer[4]=myArray[3]|0x80;
    myI2cMsg.buffer[5]=myArray[4]|0x80;
    myI2cMsg.buffer[6]=myArray[5]|0x80;
    myI2cMsg.buffer[7]=myArray[6]|0x80;
    myI2cMsg.buffer[8]=myArray[7]|0x80;
    myI2cMsg.buffer[9]=myArray[8]|0x80;
    myI2cMsg.buffer[10]=myArray[9]|0x80;
    myI2cMsg.buffer[11]=myArray[10]|0x80;
    myI2cMsg.buffer[12]=myArray[11]|0x80;
    myI2cMsg.buffer[13]=myArray[12]|0x80;
    myI2cMsg.buffer[14]=myArray[13]|0x80;
    myI2cMsg.buffer[15]=myArray[14]|0x80;
    myI2cMsg.buffer[16]=myArray[15]|0x80;
    myI2cMsg.length = LCD_LINELENGTH;
    myI2c.write(myI2cMsg);
    return true; // should actually check if the i2c transactions are ok
}


void lcd::initialize (void)
{
    qDebug()<< "lcd initialize";


}
