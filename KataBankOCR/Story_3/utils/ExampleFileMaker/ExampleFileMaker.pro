#-------------------------------------------------
#
# Project created by QtCreator 2013-01-04T20:08:20
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ExampleFileMaker
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../recognizer.cpp

INCLUDEPATH += ../..
DEPENDPATH += $$INCLUDEPATH

HEADERS += \
    ../../recognizer.h
