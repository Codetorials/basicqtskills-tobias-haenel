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
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

INCLUDEPATH += \
    $$PWD/include \
    $$PWD/src

TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/MyApplication.cpp \
    src/Worker.cpp \
    src/FunctionStatWorker.cpp \
    src/FunctionValueWorker.cpp \
    src/FunctionValueProducer.cpp \
    src/FunctionValueConsumer.cpp \
    src/FunctionSample.cpp

HEADERS += \
    include/MyApplication.h \
    include/Worker.h \
    include/FunctionStatWorker.h \
    include/FunctionValueConsumer.h \
    include/FunctionValueProducer.h \
    include/FunctionValueWorker.h \
    include/FunctionTypes.h \
    include/FunctionSample.h
