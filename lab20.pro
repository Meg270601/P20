#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app


SOURCES += main.cpp \
    send.cpp \
    cereal.cpp \
    decereal.cpp \
    receive.cpp

HEADERS  += \
    send.h \
    cereal.h \
    safe_queue.h \
    decereal.h \
    receive.h

FORMS    += \
    send.ui \
    receive.ui

LIBS += -L/usr/local/lib -lwiringPi -lpthread

CONFIG += c++11
