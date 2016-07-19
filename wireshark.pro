QT += core
QT -= gui

CONFIG += c++11

TARGET = wireshark
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    core.cpp

DISTFILES += \
    fortune \
    data \
    dataV2 \
    report.csv

HEADERS += \
    core.h
