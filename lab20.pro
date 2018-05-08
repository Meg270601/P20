#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20(1)
TEMPLATE = app


SOURCES += main.cpp \
    send.cpp \
    cereal.cpp \
    receiver.cpp \
    decereal.cpp

HEADERS  += \
    send.h \
    cereal.h \
    receiver.h \
    safe_queue.h \
    decereal.h

FORMS    += \
    send.ui \
    receive.ui

LIBS += -L/usr/local/lib -lwiringPi -lpthread

CONFIG += c++11
