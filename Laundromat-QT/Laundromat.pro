#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T20:40:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Laundromat
TEMPLATE = app

LIBS = -ldl


SOURCES += main.cpp\
        mainwindow.cpp \
    serverconnectwindow.cpp \
    RigidSpectreNETConnector.cpp

HEADERS  += mainwindow.h \
    serverconnectwindow.h \
    RigidSpectreNETConnector.h

FORMS    += mainwindow.ui \
    serverconnectwindow.ui
