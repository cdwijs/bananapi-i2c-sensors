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
    lcd.cpp

HEADERS  += mainwindow.h \
    i2c.h \
    sensor.h \
    integrator.h \
    lcd.h

FORMS    += mainwindow.ui
