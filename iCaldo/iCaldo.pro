TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += include /usr/local/include
QMAKE_CXXFLAGS += -std=c++11

SOURCES += \
    src/i2c_device.cpp \
    src/i2c_linux_device.cpp \
    src/icaldo.cpp \
    src/mcp4725.cpp \
    src/smbus_device.cpp \
    src/smbus_linux_device.cpp \
    src/wire_1_linux.cpp \
    src/wire_1.cpp

LIBS += -L/usr/local/lib
LIBS += -lboost_thread

include(deployment.pri)
qtcAddDeployment()
