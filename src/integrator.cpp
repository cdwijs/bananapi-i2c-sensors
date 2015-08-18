#include "integrator.h"
#include <QDebug>
//#include "sensor.h" // no longer needed
#include "sensor_tc74a4.h"
#include "sensor_mcp9800a0.h" //also for MCP9801 and TCN75A
#include "sensor_se95d.h" //also for LM75AD LM75BD and PCT2075D
#include "sensor_emc1001.h"
#include "sensor_hih6030.h"
#include "sensor_mpl115a2.h"
#include "sensor_at42qt1070.h"

#include "lcd.h"
#include <QString>

sensor_MCP9800A0 myMCP9800A0(0x48); //0.125^C resolution
sensor_MCP9800A0 myMCP9801(0x49);   //0.125^C resolution
sensor_MCP9800A0 myTCN75A(0x4A);    //0.125^C resolution
sensor_TC74A4 myTC74A4(0x4C);       //1^C resolution

sensor_SE95D mySE95D(0x4F);
sensor_SE95D myLM75AD(0x4B);
sensor_SE95D myLM75BD(0x4E);
sensor_SE95D myPCT2075D(0x28);

sensor_EMC1001 myEMC1001(0x38);
sensor_HIH6030 myHIH6030(0x27);

sensor_MPL115A2 myMPL115A2(0x60);

sensor_AT42QT1070 myAT42QT1070(0x1B);

float myTemp27;
float myHumi27;
float myTemp28;
float myTemp38;
float myTemp48;
float myTemp49;
float myTemp4A;
float myTemp4B;
float myTemp4C;
float myTemp4E;
float myTemp4F;
float myPress60;
unsigned char myKeys1B;

lcd myLcd;

bool myResult;

QString line0;
QString line1;

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
    myMCP9800A0.getTemperature(&myTemp48);
    myMCP9801.getTemperature(&myTemp49);
    myTCN75A.getTemperature(&myTemp4A);
    myTC74A4.getTemperature(&myTemp4C);

    mySE95D.getTemperature(&myTemp4F);
    myLM75AD.getTemperature(&myTemp4B);
    myLM75BD.getTemperature(&myTemp4E);
    myPCT2075D.getTemperature(&myTemp28);

    myEMC1001.getTemperature(&myTemp38);

    myHIH6030.getTemperature(&myTemp27);
    myHIH6030.getHumidity(&myHumi27);

    myMPL115A2.getPressure(&myPress60);

    myAT42QT1070.getKeys(&myKeys1B);

    line0.sprintf("%.4f %.4f ",myHumi27,myTemp27);
    line1.sprintf("%.4f 0x%x ",myPress60,myKeys1B);

    myLcd.write(line0,0);
    myLcd.write(line1,1);
    return true;
}

bool integrator::initialize(void)
{
    qDebug()<< "integrator initialize";
    myMCP9800A0.initialize();
    myMCP9801.initialize();
    myTCN75A.initialize();
    myTC74A4.initialize();

    mySE95D.initialize();
    myLM75AD.initialize();
    myLM75BD.initialize();
    myPCT2075D.initialize();

    myEMC1001.initialize();

    myHIH6030.initialize();

    myMPL115A2.initialize();

    myAT42QT1070.initialize();

    return true;
}
