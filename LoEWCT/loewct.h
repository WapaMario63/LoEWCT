#ifndef LOEWCT_H
#define LOEWCT_H

#include <QList>

#include "mainwindow.h"
#include "player.h"
#include "maps.h"

/// THE CORE OF [LoEWCT] \\\
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

    //QList<Mobzone*> mobzones;
    //QList<Mob*> mobs;

private:
    QTcpServer* tcpServer;
    QList<QPair<QTcpSocket*, QByteArray*>> tcpClientsList;
    QTcpSocket remoteLoginSock; // Socket to the remote login server, if we use one
    QByteArray* tcpReceivedDatas;

    QTimer* pingTimer;
    //Sync sync
    bool* usedIds;
};

extern MainWindow win;
extern LoEWCT loe;

#endif // LOEWCT_H
