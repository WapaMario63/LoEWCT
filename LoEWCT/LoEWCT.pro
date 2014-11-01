#-------------------------------------------------
#
# Project created by QtCreator 2014-09-09T16:49:32
#
#-------------------------------------------------

QT       += core gui widgets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoEWCT
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp \
    tcp.cpp \
    udp.cpp \
    serverSettingsWidget.cpp \
    playercontrols.cpp \
    loemoviemakertools.cpp \
    loewctSettingsWidget.cpp \
    datatype.cpp \
    serialize.cpp \
    utils.cpp \
    loewct.cpp \
    sync.cpp \
    player.cpp \
    pony.cpp \
    scene.cpp \
    sendClientMessages.cpp \
    receiveClientMessages.cpp \
    message.cpp \
    pingTimeout.cpp \
    receiveClientAck.cpp \
    $$files(/pce/QuaZip/*.cpp) \
    $$files(/pce/QuaZip/*.c) \
    chat.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    settings.h \
    udp.h \
    serverSettingsWidget.h \
    playercontrols.h \
    loemoviemakertools.h \
    loewctSettingsWidget.h \
    datatype.h \
    serialize.h \
    message.h \
    utils.h \
    loewct.h \
    sync.h \
    player.h \
    pony.h \
    sceneEntity.h \
    statsComponent.h \
    sendmessage.h \
    scene.h \
    receiveClientAck.h \
    $$files(/pce/QuaZip/*.h) \
    chat.h \
    database.h

FORMS    += mainwindow.ui \
    serverSettingsWidget.ui \
    playercontrols.ui \
    loemoviemakertools.ui \
    loewctSettingsWidget.ui

# Configuration to use C++11 (always make the C lowercase so it works on Mac and Linux, Windows doesn't care)
CONFIG += c++11

RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/pce/libs/ -lzdll
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/pce/libs/ -lzdlld
else:unix: LIBS += -L$$PWD/pce/libs/ -lzdll

INCLUDEPATH += $$PWD/pce/libs
DEPENDPATH += $$PWD/pce/libs
