#include "integrator.h"
#include <QDebug>
#include "sensor.h"

sensor mySensor(1);
sensor mySensor2(3);
sensor mySensor3(5);
sensor mySensor4(7);
sensor mySensor5(11);


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
    mySensor2.getValue();
    mySensor3.getValue();
    mySensor4.getValue();
    mySensor5.getValue();
    return true;
}

bool integrator::initialize(void)
{
    qDebug()<< "integrator initialize";
    mySensor.initialize();
    return true;
}
