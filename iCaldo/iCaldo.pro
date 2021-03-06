TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

linux-rasp-pi-g++{

DEFINES += BOOST_ALL_DYN_LINK

INCLUDEPATH += ./include

QMAKE_CXXFLAGS += -std=c++11

HEADERS += ./include/*.h \
    include/controller.h \
    include/communication.h

SOURCES += \
    src/i2c_device.cpp \
    src/i2c_linux_device.cpp \
    src/icaldo.cpp \
    src/mcp4725.cpp \
    src/smbus_device.cpp \
    src/smbus_linux_device.cpp \
    src/controller.cpp \
    src/thermometer.cpp \
    src/thermometer_linux.cpp

LIBS += -L~/arjan/rpi/raspbian/usr/lib
LIBS += -lboost_thread -lboost_system -lboost_regex -lboost_unit_test_framework -lboost_log -lpthread

include(deployment.pri)
qtcAddDeployment()
}
