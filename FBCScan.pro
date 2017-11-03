QT       += core gui
QT       += sql
QT       += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FBCScan
TEMPLATE = app

SOURCES += main.cpp\
        analyzetraffic.cpp \
    sqlhandler.cpp \
    general/generalthreats.cpp \
    code_grant/threatscodegrant.cpp \
    implicit_grant/threatsimplicitgrant.cpp \
    analyzationdetails.cpp \
    analyzationstatistics.cpp

HEADERS  += analyzetraffic.h \
    sqlhandler.h \
    general/generalthreats.h \
    code_grant/threatscodegrant.h \
    implicit_grant/threatsimplicitgrant.h \
    analyzationdetails.h \
    analyzationstatistics.h

FORMS    += analyzetraffic.ui \
    analyzationstatistics.ui \
    analyzationdetails.ui


# install
target.path = /home/julia/Desktop/BA/Tool_FBCScan/FBCScan
INSTALLS += target
