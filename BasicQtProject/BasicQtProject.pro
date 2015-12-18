#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T15:13:01
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = BasicQtProject
CONFIG   += c++11
CONFIG   -= app_bundle

INCLUDEPATH += \
    $$PWD/include \
    $$PWD/src

TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/MyApplication.cpp \
    src/Worker.cpp \
    src/Producer.cpp \
    src/Consumer.cpp

HEADERS += \
    include/MyApplication.h \
    include/Worker.h \
    include/Producer.h \
    include/Consumer.h
