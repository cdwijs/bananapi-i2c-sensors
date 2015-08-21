#include "gpio.h"
#include <QDebug>

gpio::gpio(unsigned char numio, bool diroutput)
{
    bool result=false;
    dirOutput = diroutput;
    myNumIo = numio;
    QString myString;
    //set pin to gpio
    myString.sprintf("%d",myNumIo);
    file.setFileName("/sys/class/gpio/export");
    if (file.open(QFile::WriteOnly))
    {
        opResult = file.write(myString.toLocal8Bit());
        qDebug("%d bytes written",opResult);
        file.close();
    }
    //write "in" or "out" to direction file
    myString.sprintf("/sys/class/gpio/gpio%d/direction",myNumIo);
    file.setFileName(myString);
    if (dirOutput)
    {

        myString = "out";
    }
    else
    {
        myString = "in";
    }
    if (file.open(QFile::WriteOnly))
    {
        opResult = file.write(myString.toLocal8Bit());
        qDebug("%d bytes written",opResult);
        file.close();
    }
    //open the file with value
    myString.sprintf("/sys/class/gpio/gpio%d/value",myNumIo);
    file.setFileName(myString);
    if (dirOutput)
    {
        if (file.open(QFile::WriteOnly))
        {
            qDebug() << file.fileName() << "opened for writing";
        }
    }
    else
    {
        if (file.open(QFile::ReadOnly))
        {
            qDebug() << file.fileName() << "opened for reading";
        }
    }
    //return result;
}

gpio::~gpio()
{
    qDebug() <<  "closing " << file.fileName();
    file.close();
}

int gpio::setVal(bool value)
{
    QString myString;
    if (dirOutput)
    {
        if (value)
        {
            myString = "1";
        }
        else
        {
            myString = "0";
        }
        opResult = file.write(myString.toLocal8Bit());
        file.flush();
        qDebug("%d bytes written",opResult);
    }
    else
    {
        return -1;
    }
    return 0;
}

bool gpio::getVal(void)
{
    unsigned char mychar;
    QByteArray bytearray;
    file.reset();
    bytearray = file.readAll();
    mychar = bytearray.at(0);
    return (mychar == '1');
}
