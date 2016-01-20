#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T20:40:05
#
#-------------------------------------------------

QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Laundromat
TEMPLATE = app

LIBS = -ldl


SOURCES += main.cpp\
        mainwindow.cpp \
    RigidSpectreNETConnector.cpp \
    laundromatmachine.cpp

HEADERS  += mainwindow.h \
    RigidSpectreNETConnector.h \
    laundromatmachine.h

FORMS    += mainwindow.ui
