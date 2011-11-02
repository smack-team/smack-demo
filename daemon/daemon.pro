QT       += core dbus network
QT       -= gui

TARGET = demo-daemon
CONFIG   += console link_pkgconfig
CONFIG   -= app_bundle
TEMPLATE = app
PKGCONFIG += libsmack

SOURCES += main.cpp \
    dbusserviceifadaptor.cpp \
    dbusservice.cpp \
    engine.cpp \
    smacklabelif.cpp

HEADERS += \
    dbusserviceifadaptor.h \
    dbusservice.h \
    engine.h \
    smack-demo-common.h \
    smacklabelif.h

OTHER_FILES += \
    com.smack.demo.xml \
    com.smack.demo.service \
    com.smack.demo.conf

target.path = $$(DESTDIR)/usr/bin

service.path = $$(DESTDIR)/usr/share/dbus-1/services
service.files = com.smack.demo.service

configuration.path = $$(DESTDIR)/etc/dbus-1/session.d
configuration.files = com.smack.demo.conf

dbusInterface.path = $$(DESTDIR)/usr/share/dbus-1/interfaces
dbusInterface.files = com.smack.demo.xml

INSTALLS += target service configuration dbusInterface
