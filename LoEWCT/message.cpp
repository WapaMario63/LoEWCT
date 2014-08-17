#include "message.h"

#include "player.h"
#include "loewct.h"
#include "serialize.h"
//#include "mob.h"
//#include "mobsparser.h"
//#include "mobstats.h"
//#include "animation.h"
#include "settings.h"

// File-Global game-entering mutex (to prevent multiple instantiates/clones)
static QMutex levelLoadMutex;

void sendPonies(Player *player)
{
    // The full request is like a normal sendPonies but with all the serialized ponies at the end
    QList<Pony> ponies = Player::loadPonies(player);
    quint32 poniesDataSize = 0;

    for (int i=0; i<ponies.size(); i++) poniesDataSize += ponies[i].ponyData.size();

    QByteArray data(5, 0);
    data[0] = 1; // Request Number from client

    // Number of Ponies
    data[1] = (quint8)(ponies.size()&0xFF);
    data[2] = (quint8)((ponies.size()>>8)&0xFF);
    data[3] = (quint8)((ponies.size()>>16)&0xFF);
    data[4] = (quint8)((ponies.size()>>24)&0xFF);

    for (int i=0; i<ponies.size(); i++) data += ponies[i].ponyData;

    win.logMessage(LOG_INFO+QObject::tr("UDP: Sending characters data to %1").arg(+player->pony.netviewId));

    sendMessage(player, MsgUserReliableOrdered4, data);
}

void sendEntitiesList(Player *player)
{
    levelLoadMutex.lock(); // Protect player->inGame

    // Not yet in-game, send player's ponies list (Character Selection screen (scene))
    if (player->inGame == 0)
    {
        levelLoadMutex.unlock();

        win.logMessage(LOG_INFO+QObject::tr("UDP: Sending ponies list to %1").arg(player->name));

        sendPonies(player);
        return;
    }
    else if (player->inGame > 1) // not supposed to happen, let's do it anyway
    {
        //levelLoadMutex.unlock();
        win.logMessage(LOG_INFO+QObject::tr("UDP: Entities list already sent to %1, Resending Anyway").arg(player->pony.netviewId));
        //return;
    }
    else // Loading Finished, sending entities list
    {
        win.logMessage(LOG_INFO+QObject::tr("UDP: Sending entities list to %1").arg(player->pony.netviewId));
    }

    // Spawn all players on the client
    Scene* scene = findScene(player->pony.sceneName);
    for (int i=0; i<scene->players.size(); i++) sendNetviewInstantiate(&scene->players[i]->pony, player);

    // Send npcs
    for (int i=0; i<loe.npcs.size(); i++)
    {
        if (loe.npcs[i]->sceneName.toLower() == player->pony.sceneName.toLower())
        {
            win.logMessage(LOG_INFO+QObject::tr("UDP: Sending NPC %1").arg(loe.npcs[i]->name));
            sendNetviewInstantiate(loe.npcs[i], player);
        }
    }
    // Send Mobs
    for (int i=0; loe.mobs.size(); i++)
    {
        if (loe.mobs[i]->sceneName.toLower() == player->pony.sceneName.toLower())
        {
            win.logMessage(LOG_INFO+QObject::tr("UDP: Sending mobs %1").arg(loe.mobs[i]->modelName));
        }
    }

    // REMINDER: Remove this once mobzones are fully functional
    // Spawn some mobs in Zecoras
     //if (scene->name.toLower() == "zecoras")
       //{
         //sendNetviewInstantiate(player, "mobs/dragon", win.getNewId(),win.getNewNetviewId(), {-33.0408, 0.000425577, 101.766}, {0, -1,0,1});
      // }

    player->inGame = 2;
    levelLoadMutex.unlock();

    // Send stats of the client's pony
    sendSetMaxStatRPC(player, 0, 100);
    sendSetStatRPC(player, 0, 100);
    sendSetMaxStatRPC(player, 1, 100);
    sendSetStatRPC(player, 1, 100);
}

void sendPonySave(Player *player, QByteArray msg)
{
    if (player->inGame < 2) // Not Supposed to happen, ignoring the request
    {
         win.logMessage(LOG_INFO+QObject::tr("UDP: Savegame requested too soon by %1").arg(player->pony.netviewId));
         return;
    }

    quint16 netviewId = (quint8)msg[6] += ((quint16)(quint8)msg[7]<<8);
    Player* refresh = Player::findPlayer(loe.udpPlayers, netviewId); // Find players

    // If we find a matching NPC, send him ate exits (well it was misspelled in the original code, so I think its that)
    Pony* npc = NULL;
    for (int i=0; i<loe.npcs.size(); i++)
        if (loe.npcs[i]->netviewId == netviewId)
            npc = loe.npcs[i];

    if (npc != NULL)
    {
        win.logMessage(LOG_INFO+QObject::tr("UDP: Sending ponyData and worn items for NPC"));
    }
}
