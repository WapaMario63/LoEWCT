#include <QFile>
#include <QDir>

#include "player.h"
#include "pony.h"
#include "mainwindow.h"
#include "loewct.h"
#include "utils.h"
#include "serialize.h"
#include "message.h"
#include "sendMessage.h"
#include "scene.h"
//#include "items.h"
//#include "packetloss.h"
#include "settings.h"

Player::Player()
    : pony{Pony(this)}
{
    isConnected = false;
    inGame = 0;
    nReceivedDups = 0;
    lastPingNumber = 0;
    lastPingTime = timestampNow();
    port = 0;
    IP = QString();
    receivedDatas = new QByteArray();
    for (int i=0; i<33; i++) udpSequenceNumbers[i] = 0;
    for (int i=0; i<33; i++) udpRecvSequenceNumbers[i] = 0;
    udpRecvMissing.clear();

    // Prepare timers
    chatRollCooldownEnd = QDateTime::currentDateTime();
    udpSendReliableTimer = new QTimer;
    udpSendReliableTimer->setInterval(UDP_RESEND_TIMEOUT);
    udpSendReliableTimer->setSingleShot(true);
    connect(udpSendReliableTimer, SIGNAL(timeout()), this, SLOT(udpResentLast()));
    udpSendReliableGroupTimer = new QTimer;
    udpSendReliableGroupTimer->setInterval(UDP_GROUPING_TIMEOUT);
    udpSendReliableGroupTimer->setSingleShot(true);
    connect(udpSendReliableGroupTimer, SIGNAL(timeout()), this, SLOT(udpDelayedSend()));
}

Player::~Player()
{
    disconnect(udpSendReliableGroupBuffer);
    disconnect(udpSendReliableTimer);
    delete udpSendReliableGroupTimer;
    delete udpSendReliableTimer;
    delete receivedDatas;
}

void Player::reset()
{
    name.clear();
    isConnected = false;
    inGame = 0;
    nReceivedDups = 0;
    lastPingNumber = 0;
    lastPingTime=timestampNow();
    port = 0;
    IP.clear();
    receivedDatas->clear();
    lastValidReceivedAnimation.clear();
    pony = Pony(this);
    for (int i=0;i<33;i++) udpSequenceNumbers[i]=0;
    for (int i=0;i<33;i++) udpRecvSequenceNumbers[i]=0;
    udpRecvMissing.clear();
}

void Player::resetNetwork()
{
    isConnected = false;
    nReceivedDups = 0;
    lastPingNumber = 0;
    lastPingTime=timestampNow();
    port = 0;
    IP.clear();
    receivedDatas->clear();
    for (int i=0;i<33;i++) udpSequenceNumbers[i]=0;
    for (int i=0;i<33;i++) udpRecvSequenceNumbers[i]=0;
    udpRecvMissing.clear();
}

// Player Finders/Player Look Up functions
// Start
Player* Player::findPlayer(QList<Player *> &players, QString uname)
{
    for (int i=0; i<players.size(); i++)
    {
        if (players[i]->name == uname) return players[i];
    }

    Player* emptyPlayer = new Player();
    return emptyPlayer;
}

Player* Player::findPlayer(QList<Player *> &players, QString uIP, quint16 uport)
{
    for (int i=0; i<players.size(); i++)
    {
        if (players[i]->IP == uIP && players[i]->port == uport) return players[i];
    }

    Player* emptyPlayer = new Player();
    return emptyPlayer;
}

Player* Player::findPlayer(QList<Player *> &players, quint16 netviewId)
{
    for (int i=0; i<players.size(); i++)
    {
        if (players[i]->pony.netviewId == netviewId) return players[i];
    }

    Player* emptyPlayer = new Player();
    return emptyPlayer;
}
// End

// Save/Load Player data (.ldf (LoE Data File) and .lpd (LoE Player Data) files)
// Start
bool Player::savePlayers(QList<Player *>& playersData)
{
    QFile playersFile("data/players/players.ldf");
    if (!playersFile.exists())
    {
        win.logMsg(QObject::tr("%1 UDP: Player Database (players.ldf) not found, creating a fresh new one...").arg(LOG_INFO));
        playersFile.open(QIODevice::WriteOnly);
        playersFile.close();
        win.logMsg(QObject::tr("%1 UDP: Player Database (players.ldf) created succesfully.").arg(LOG_INFO));
    }
    if (!playersFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        win.logMsg(QObject::tr("%1 UDP: Error saving Player Database (players.ldf). (STOPPING GAME SERVER!)").arg(LOG_SEVERE));
        loe.stopGameServer();
        return false;
    }

    for (int i=0; i <playersData.size(); i++)
    {
        playersFile.write(playersData[i]->name.toLatin1());
        playersFile.write("\31");
        playersFile.write(playersData[i]->passhash.toLatin1());
        if (i + 1 != playersData.size()) playersFile.write("\n");
    }
    return true;
}

QList<Player*> Player::loadPlayers()
{
    QList<Player*> players;
    QFile playersFile("data/players/players.ldf");
    if (!playersFile.open(QIODevice::ReadOnly))
    {
        win.logMsg(QObject::tr("%1 UDP: Error Loading Player Database (players.ldf). STOPPING GAME SERVER!").arg(LOG_SEVERE));
        loe.stopGameServer();
        return players;
    }
    QList<QByteArray> data = playersFile.readAll().split('\n');
    if (data.size() == 1 && data[0].isEmpty())
    {
        win.logMsg(QObject::tr("%1 UDP: Player Database is empty, continuing.").arg(LOG_INFO));
        return players;
    }
    for (int i=0; i<data.size(); i++)
    {
        QList<QByteArray> line = data[i].split('\31');
        if (line.size() != 2)
        {
            win.logMsg(QObject::tr("%1 UDP: Error Loading Player Database (players.ldf). STOPPING GAME SERVER!").arg(LOG_SEVERE));
            loe.stopGameServer();
            return players;
        }
        Player* newPlayer = new Player;
        newPlayer->name = line[0];
        newPlayer->passhash = line[1];
        players << newPlayer;
    }
    win.logMsg(QObject::tr("%1 UDP: Got %2 players in database").arg(LOG_INFO).arg(QString().setNum(players.size())));
    return players;
}

void Player::savePonies(Player *player, QList<Pony> ponies)
{
    win.logMsg(QObject::tr("%1 UDP: Saving Ponies for %2 (%3)").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId).arg(player->name)));

    QDir playerPath(QDir::currentPath());
    playerPath.cd("data");
    playerPath.cd("players");
    playerPath.mkdir(player->name.toLatin1());

    QFile file(QDir::currentPath()+"/data/players/"+player->name.toLatin1()+"/ponies.lpd");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    for (int i=0; i<ponies.size(); i++)
    {
        file.write(ponies[i].ponyData);
        file.write(vectorToData(ponies[i].pos));
        file.write(stringToData(ponies[i].sceneName.toLower()));
    }
}

QList<Pony> Player::loadPonies(Player *player)
{
    QList<Pony> ponies;
    QFile file(QDir::currentPath()+"/data/players/"+player->name.toLatin1()+"ponies.lpd");
    if (!file.open(QIODevice::ReadOnly)) return ponies;

    QByteArray data = file.readAll();

    int i=0;
    while (i < data.size())
    {
        Pony pony(player);

        // read the ponyData
        unsigned strlen;
        unsigned lensize = 0;
        {
            unsigned char num3; int num=0, num2=0;
            do
            {
                num3 = data[i+lensize]; lensize++;
                num |= (num3 & 0x7f) << num2;
                num2 += 7;
            } while ((num3 & 0x80) != 0);
            strlen = (uint) num;
        }

#if USE_BABSCON_CLIENT
        int ponyDataSize = strlen+lensize+43;
#elif USE_BRONYCON_CLIENT
        int ponyDataSize = strlen+lensize+PONYDATA_SIZE;
#endif
        pony.ponyData = data.mid(i, ponyDataSize);
        pony.name = dataToString(pony.ponyData); // The name is the first element
        //win.logMsg("Found pony : "+pony.name);
        i += ponyDataSize;

        // Read Position
        UVector pos = dataToVector(data.mid(i, 12));
        pony.pos = pos;
        i += 12;

        // Read sceneName
        unsigned strlen2;
        unsigned lensize2 = 0;
        {
            unsigned char num3; int num=0, num2=0;
            do
            {
                num3 = data[i+lensize2]; lensize2++;
                num |= (num3 & 0x7f) << num2;
                num2 += 7;
            } while ((num3 & 0x80) != 0);
            strlen2 = (uint) num;
        }
        pony.sceneName = data.mid(i+lensize2, strlen2).toLower();
        i += strlen2 + lensize2;

        // Create quests
        /*for (int i=0; i<win.quests.size(); i++)
        {
            Quest quest = win.quests[i];
            quest.setOwner(player);
            pony.quests << quest;
        }*/

        ponies << pony;
    }
    return ponies;
}
// End

void Player::removePlayer(QList<Player *> &players, QString uIP, quint16 uport)
{
    for (int i=0; i<players.size(); i++)
    {
        if (players[i]->IP == uIP && players[i]->port == uport) players.removeAt(i);
    }
}

// Clears memory from the server of the player that disconnected.
// Also saves that player's data
void Player::disconnectPlayerCleanUp(Player *player)
{
    static QMutex playerCleanupMutex;

    // Save the player's pony
    QList<Pony> ponies = loadPonies(player);
    for (int i=0; i<ponies.size(); i++)
    {
        if (ponies[i].ponyData == player->pony.ponyData) ponies[i] = player->pony;
    }
    savePonies(player, ponies);
    player->pony.saveQuests();
    player->pony.saveInventory();

    QString uIP = player->IP;
    quint16 uPort = player->port;

    Scene* scene = findScene(player->pony.sceneName);
    if (scene->name.isEmpty())
        win.logMsg(QObject::tr("%1 UDP: Can't find scene for player cleanup").arg(LOG_ERROR));

    //win.logMsg("[INFO] player CleanUp locking");
    playerCleanupMutex.lock();
    removePlayer(scene->players, uIP, uPort);
    //for (int i=0; i<scene->players.size(); i++)
    //    sendNetviewRemove(scene->players[i], player->pony.netviewId);
    player->udpDelayedSend(); // We're about to remove the player, we can't delay the send
    player->udpSendReliableTimer->stop();
    player->udpSendReliableGroupTimer->stop();
    removePlayer(loe.udpPlayers, uIP, uPort);
    delete player;
    //win.logMsg("[INFO] player CleanUp unlocking");
    playerCleanupMutex.unlock();
}

void Player::udpResendLast()
{

}

void Player::udpDelayedSend()
{

}
