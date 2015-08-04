#include "integrator.h"
#include <QDebug>
#include "sensor.h"

sensor mySensor;
sensor mySensor2;
sensor mySensor3;
sensor mySensor4;
sensor mySensor5;


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
