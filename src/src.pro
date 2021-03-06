#-------------------------------------------------
#
# Project created by QtCreator 2015-08-03T13:28:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = src
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    i2c.cpp \
    sensor.cpp \
    integrator.cpp \
    lcd.cpp \
    sensor_tc74a4.cpp \
    sensor_mcp9800a0.cpp \
    sensor_se95d.cpp \
    sensor_emc1001.cpp \
    sensor_hih6030.cpp \
    sensor_mpl115a2.cpp \
    sensor_at42qt1070.cpp \
    gpio.cpp

HEADERS  += mainwindow.h \
    i2c.h \
    sensor.h \
    integrator.h \
    lcd.h \
    sensor_tc74a4.h \
    sensor_mcp9800a0.h \
    sensor_se95d.h \
    sensor_emc1001.h \
    sensor_hih6030.h \
    sensor_mpl115a2.h \
    sensor_at42qt1070.h \
    gpio.h

FORMS    += mainwindow.ui
