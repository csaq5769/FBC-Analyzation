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
    websitedetails.cpp \
    statistics.cpp

HEADERS  += analyzetraffic.h \
    sqlhandler.h \
    general/generalthreats.h \
    code_grant/threatscodegrant.h \
    implicit_grant/threatsimplicitgrant.h \
    websitedetails.h \
    statistics.h

FORMS    += analyzetraffic.ui \
    websitedetails.ui \
    statistics.ui


# install
target.path = /home/julia/Desktop/BA/Tool_FBCScan/FBCScan
INSTALLS += target
