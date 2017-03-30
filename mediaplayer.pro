#-------------------------------------------------
#
# Project created by QtCreator 2016-06-18T12:38:58
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mediaplayer
TEMPLATE = app


SOURCES += main.cpp\
        mediaplayer.cpp
maemo* {
    DEFINES += PLAYER_NO_COLOROPTIONS
}

HEADERS  += mediaplayer.h

FORMS    += mediaplayer.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    icons/openicon.png
