#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMutex>
#include <QByteArray>
#include <QDateTime>

#include "dataType.h"
//#include "quest.h"
#include "sceneEntity.h"
#include "statsComponent.h"
#include "settings.h"
#include "pony.h"

class Player : QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Player)

public:
    Player();
    ~Player();
    static void savePonies(Player* player, QList<Pony> ponies);
    static QList<Pony> loadPonies(Player* player);
    static bool savePlayers(QList<Player*>& playersData);
    static QList<Player*> loadPlayers();
    static Player* findPlayer(QList<Player*>& players, QString uname);
    static Player* findPlayer(QList<Player*>& players, QString uIP, quint16 uport);
    static Player* findPlayer(QList<Player*>& players, quint16 netviewId);
    static void removePlayer(QList<Player*>& players, QString uIP, quint16 uport);
    static void disconnectPlayerCleanUp(Player* player);

public slots:
    void udpResendLast(); // If a reliable msg wasn't ACK'd yet, resend it now.
    void udpDelayedSend(); // Enqueue and send the content of the player's grouped message buffer


public:
    void reset(); // Reconstructs an empty Player
    void resetNetwork(); // Resets all the network-related members

public:
    QString IP;
    quint16 port;
    QString name;
    QString passhash;
    float lastPingTime;
    int lastPingNumber;
    bool isConnected;
    quint16 udpSequenceNumbers[33]; // Next seq number to use when sending a message
    quint16 udpRecvSequenceNumbers[33]; // Last seq number received
    QByteArray *receivedDatas;
    QVector<MessageHead> udpRecvMissing; // When a message is skipped, mark it as missing and wait for a retransmission
    QVector<QByteArray> udpSendReliableQueue; // Messages that we're sending and that aren't ACKd yet.
    QByteArray udpSendReliableGroupBuffer; // Groups the udp message in this buffer before sending them
    QTimer* udpSendReliableGroupTimer; // Delays the sending until we finished grouping the messages
    QTimer* udpSendReliableTimer; // If we didn't get an ACK before this timeouts, resend the last message
    QMutex udpSendReliableMutex; // Protects the buffer/queue/timers from concurrency hell
    Pony pony;
    QByteArray lastValidReceivedAnimation;
    quint8 inGame; // 0: Not in-game, 1: Loading (char select screen), 2: Instantiated & waiting savegame, 3: In-Game and loaded
    quint16 nReceivedDups; // Number of duplicate packets that we didn't miss and had to discard.
    QDateTime chatRollCooldownEnd; // When the cooldown for the roll chat command ends
};

#endif // PLAYER_H
