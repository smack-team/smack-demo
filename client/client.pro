QT       += core dbus network
QT       -= gui

TARGET = demo-client
CONFIG   += console
CONFIG   -= app_bundle
TEMPLATE = app

SOURCES += main.cpp \
    clientdbusif.cpp \
    serverdbus.cpp \
    client.cpp

HEADERS += clientdbusif.h \
    serverdbus.h \
    client.h


OTHER_FILES +=


target.path = $$(DESTDIR)/usr/bin

INSTALLS += target
