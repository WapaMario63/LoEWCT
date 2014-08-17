#-------------------------------------------------
#
# Project created by QtCreator 2014-08-03T18:05:21
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoEWCT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loewct.cpp \
    player.cpp \
    datatype.cpp \
    serialize.cpp \
    maps.cpp \
    quest.cpp \
    message.cpp \
    settings.cpp \
    mob.cpp \
    mobparser.cpp \
    pony.cpp

HEADERS  += mainwindow.h \
    loewct.h \
    player.h \
    datatype.h \
    serialize.h \
    statsComponent.h \
    sceneEntity.h \
    maps.h \
    quest.h \
    message.h \
    settings.h \
    mob.h \
    mobzone.h \
    mobparser.h \
    pony.h

FORMS    += mainwindow.ui

# include coreservices (required for timestamps) for mac
macx {
    QMAKE_LFLAGS += -F /System/Library/Frameworks/CoreServices.framework/
    LIBS += -framework CoreServices
}

CONFIG += C++11
