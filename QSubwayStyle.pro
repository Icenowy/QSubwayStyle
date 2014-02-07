#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T22:45:45
#
#-------------------------------------------------

QT       += core gui

TARGET = QSubwayStyle
TEMPLATE = lib
CONFIG += plugin

DESTDIR = $$[QT_INSTALL_PLUGINS]/styles

SOURCES += subwaystyleplugin.cpp \
    qsubwaystyle.cpp

HEADERS += subwaystyleplugin.h \
    qsubwaystyle.h
OTHER_FILES += QSubwayStyle.json

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
