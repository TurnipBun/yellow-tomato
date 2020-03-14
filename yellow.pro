QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = run
TEMPLATE = app
HEADERS  = analogclock.h Dialog.h
SOURCES += main.cpp analogclock.cpp Dialog.cpp
FORMS += tomato.ui
RESOURCES += resource/tomato.qrc