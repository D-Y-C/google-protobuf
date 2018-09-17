TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
            damon.pb.cc \
            damon.pb.h

INCLUDEPATH += \
    /usr/local/include/ \

LIBS +=  -L /usr/local/lib -lprotobuf -pthread


QMAKE_RPATHDIR += /usr/local/lib
