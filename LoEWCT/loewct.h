#ifndef LOEWCT_H
#define LOEWCT_H

#include <QtWidgets/QWidget>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QTcpServer>
#include <QByteArray>
#include <QDateTime>
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
#include <memory>

#include "settings.h"
#include "player.h"
#include "pony.h"
#include "scene.h"

#define GAMEDATAPATH "data/data/"
#define PLAYERSPATH "data/players/"
#define NETDATAPATH "data/netData/"
#define CONFIGFILEPATH "data/server.ini"
#define SERVERSLISTFILEPATH "data/serversList.cfg"
#define LOEWCTCONFIGFILEPATH "data/LoEWCT_config.ini"
#define MOBSPATH "data/mobZones/"

class LoEWCT : public QObject
{
    Q_OBJECT
public slots:
    void checkPingTimeouts();

public:
    LoEWCT();
    ~LoEWCT();

    // Servers
    void startLoginServer();
    void stopLoginServer(); // Only called by mainwindow if the bool version is true
    void startGameServer();
    void stopGameServer(); // Only called by mainwindow if the bool version is true

    void loadConfig();
    void saveConfig();

    int getNewNetviewId();
    int getNewId();

    // TCP stuff
public slots:
    void tcpConnectClient();
    void tcpDisconnectClient();
    void tcpProcessPendingDatagram();

public:
    void tcpProcessData(QByteArray data, QTcpSocket *socket);

    float startTimeStamp;
    QMutex lastIdMutex; // Protects lastId and lastNetviewId
    int syncInterval;

    QList<Player*> tcpPlayers; // Used by the TCP login server
    QList<Player*> udpPlayers; // Used by the UDP game server
    QList<Pony*> npcs; // List of npcs from the npcs DB
    QList<Scene> scenes; // List of scenes from the vortex DB
    //QList<Quest> quests; // List of quests from the npcs DB
    QMap<uint32_t, uint32_t> wearablePositionsMap; // Maps item IDs to their wearable positions.

public:
    QTcpServer* tcpServer;
    QUdpSocket *udpSocket;
    QList<QPair<QTcpSocket*, QByteArray*>> tcpClientsList;
    QTcpSocket remoteLoginSock;
    QByteArray* tcpReceivedDatas;
    Player* cmdPlayer;
    //std::unique_ptr<Sync> sync;

private:

    QTimer* pingTimer;
    //Sync sync;
    bool* usedids;
};

class LoEWCTThread : public QObject
{
        Q_OBJECT
public:
    void run();

    void runGameServerThread();
    void runLoginServerThread();

    bool useGameServer;
    bool useLoginServer;

    QString threadName;
};

extern LoEWCT loe;

#endif // LOEWCT_H
