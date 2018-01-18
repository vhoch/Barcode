TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    BarCodeEAN13.cpp \
    BarCode.cpp \
    BarCodeDataMatrix.cpp

HEADERS += \
    BarCodeEAN13.h \
    BarCode.h \
    BarCodeDataMatrix.h
