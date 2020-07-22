QT += core gui network widgets

TARGET = run
TEMPLATE = app
HEADERS  = analogclock.h Dialog.h
SOURCES += main.cpp analogclock.cpp Dialog.cpp TomatoState.cpp
FORMS += tomato.ui
RESOURCES += resource/tomato.qrc
CONFIG += debug