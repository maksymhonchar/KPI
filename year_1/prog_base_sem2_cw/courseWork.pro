#-------------------------------------------------
#
# Project created by QtCreator 2016-05-17T22:55:07
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += $$PWD

TARGET = courseWork
TEMPLATE = app


SOURCES += main.cpp\
        battlefieldui.cpp \
    enemy.cpp \
    stats.cpp \
    achvments.cpp \
    army.cpp \
    perksui.cpp \
    achvmentsui.cpp \
    heropowers.cpp \
    settingsui.cpp \
    rankingsui.cpp \
    player.cpp \
    gameinfo.cpp

HEADERS  += battlefieldui.h \
    enemy.h \
    stats.h \
    achvments.h \
    army.h \
    perksui.h \
    achvmentsui.h \
    heropowers.h \
    settingsui.h \
    rankingsui.h \
    player.h \
    gameinfo.h

FORMS    += battlefieldui.ui \
    perksui.ui \
    achvmentsui.ui \
    settingsui.ui \
    rankingsui.ui

RESOURCES += \
    srcfile.qrc
