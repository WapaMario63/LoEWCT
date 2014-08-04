#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>
#include <QTimer>
#include <QList>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QtConcurrent/QtConcurrentMap>
#include <QCryptographicHash>
#include <QMutex>
#include <QMap>
#include <cstdint>

// File includes of includities (is that even a word?)

#include "loewct.h"

// Define paths and files that are used frequently
#define GAMEDATAPATH "data/data/"
#define PLAYERSPATH "data/players/"
#define NETDATAPATH "data/netdata/"
#define CONFIGPATH "data/server.ini"
#define SERVERLISTPATH "data/serversList.cfg"
#define MOBZONESPATH "data/mobZones/"



namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
  Q_OBJECT

    // Main functions

public slots:
    void sendCmdLine();
    void externCmdLine(QString str);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void logMessage(QString msg);
    void logStatus(QString msg);
    void starServer();
    void stopServer(); // Only calls LoEWCT's class to set it to true

public:
    Ui::MainWindow *ui;

};

// Global extern import from main.cpp
extern MainWindow win;
extern LoEWCT loe;

#endif // MAINWINDOW_H
