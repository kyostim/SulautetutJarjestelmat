
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoCaptureExample
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += opencv4

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    bgvideoprocessor.cpp

HEADERS += \
        mainwindow.h \
    bgvideoprocessor.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
