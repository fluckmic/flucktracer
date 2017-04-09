TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += `pkg-config opencv --libs`

SOURCES += main.cpp \
    element.cpp \
    vector.cpp \
    camera.cpp \
    raytracer.cpp \
    light.cpp

HEADERS += \
    vector.h \
    element.h \
    collision.h \
    ray.h \
    camera.h \
    raytracer.h \
    light.h
