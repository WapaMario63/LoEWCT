#ifndef LOEWCT_H
#define LOEWCT_H

#include <QtWidgets/QWidget>
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

#include "mainwindow.h"
#include "player.h"
#include "maps.h"
#include "mob.h"
#include "mobparser.h"

// Define paths and files that are used frequently
#define GAMEDATAPATH "data/data/"
#define PLAYERSPATH "data/players/"
#define NETDATAPATH "data/netdata/"
#define CONFIGPATH "data/server.ini"
#define SERVERLISTPATH "data/serversList.cfg"
#define MOBZONESPATH "data/mobZones/"

// THE CORE OF [LoEWCT] \\

class Mobzone;
class Mob;

class LoEWCT : public QMainWindow
{
public slots:
    void checkPingTimeouts();

public:
    void stopServer(bool log);
    int getNewNetviewId();
    int getNewId();

public slots:
    // UDP Socket related things
    void udpProcessPendingDatagrams();
    // TCP Server And Socket related things
    void tcpConnectClient();
    void tcpDisconnectClient();
    void tcpProcessPendingDatagrams();
public:
    void tcpProcessData(QByteArray data, QTcpSocket *socket);

// General things of generalism
public:
    QUdpSocket *udpSocket;
    float startTimestamp;

    QList<Player*> tcpPlayers; // Used by the TCP Login server
    QList<Player*> udpPlayers; // Used by the UDP Game server
    QList<Pony*> npcs; // List of npcs from the npcs DB
    //QList<Quest> quests; // List of quests from the npcs DB

    QMap<uint32_t, uint32_t> wearablePositionsMap; // Maps Item IDs to their wearable positions.

    QList<Scene> scenes; // List of scenes from the vortex DB
    QMutex lastIdMutex; // Protects lastId and lastNetviewId

    QList<Mobzone*> mobzones;
    QList<Mob*> mobs;

private:
    QTcpServer* tcpServer;
    QList<QPair<QTcpSocket*, QByteArray*>> tcpClientsList;
    QTcpSocket remoteLoginSock; // Socket to the remote login server, if we use one
    QByteArray* tcpReceivedDatas;

    QTimer* pingTimer;
    //Sync sync
    bool* usedIds;
};

extern LoEWCT loe;

#endif // LOEWCT_H
