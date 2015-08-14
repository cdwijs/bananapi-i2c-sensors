#include "integrator.h"
#include <QDebug>
#include "sensor.h"
#include "lcd.h"

sensor mySensor('a');
sensor mySensor2('b');
sensor mySensor3('c');
sensor mySensor4('d');
sensor mySensor5('e');

lcd myLcd;

bool myResult;

integrator::integrator()
{
    qDebug()<< "integrator constructor";
}

integrator::~integrator()
{
    qDebug()<< "integrator destructor";
}

bool integrator::setDivider(int)
{
    qDebug()<< "integrator setDivider";
    return true;
}

bool integrator::update(void)
{
    qDebug()<< "integrator update";
    mySensor.getValue();
    //myLcd.write("FEDCBA9876543210","ponmlkjihgfedcba");
    mySensor2.getValue();
    //myLcd.write("Sensor2         ","GetValue        ");
    mySensor3.getValue();
    //myLcd.write("Sensor3         ","GetValue        ");
    mySensor4.getValue();
    //myLcd.write("Sensor4         ","GetValue        ");
    mySensor5.getValue();
    //myLcd.write("Sensor5         ","GetValue        ");
    return true;
}

bool integrator::initialize(void)
{
    qDebug()<< "integrator initialize";
    mySensor.initialize();
    return true;
}
