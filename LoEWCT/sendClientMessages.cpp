#include "message.h"
#include "player.h"
#include "pony.h"
#include "loewct.h"
#include "mainwindow.h"
#include "serialize.h"
//#include "mob.h"
//#include "mobsparser.h"
//#include "mobstats.h"
//#include "animation.h"
#include "settings.h"

// File-global game-entering mutex (to prevent multiple instantiates)
static QMutex levelLoadMutex;

void sendPonies(Player *player)
{
    // The full request is like a normal sendPonies but with all the serialized ponies at the end
    QList<Pony> ponies = Player::loadPonies(player);
    quint32 poniesDataSize = 0;

    for (int i=0; i<ponies.size(); i++) poniesDataSize += ponies[i].ponyData.size();

    QByteArray data(5,0);
    data[0] = 1; // Client RPC request number
    data[1] = (quint8)(ponies.size() &0xFF); // Number of Ponies
    data[2] = (quint8)((ponies.size() >> 8) &0xFF); // ''
    data[3] = (quint8)((ponies.size() >> 16) &0xFF); // ''
    data[4] = (quint8)((ponies.size() >> 24) &0xFF); // ''

    for (int i=0; i<ponies.size(); i++) data += ponies[i].ponyData;

    win.logMsg(QObject::tr("%1 UDP: Sending pony datas to %2").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));
    sendMessage(player, MsgUserReliableOrdered4, data);
}

void sendEntitiesList(Player *player)
{
    levelLoadMutex.lock(); // Protect player->inGame
    if (player->inGame == 0) // Not yet in-game, send player's ponies list (Character Select screen)
    {
        levelLoadMutex.unlock();

        win.logMsg(QObject::tr("%1 UDP: Sending ponies list"));
        sendPonies(player);
        return;
    }
    else if (player->inGame > 1) // Not supposed to happen, let's do it anyway
    {
        //levelLoadMutex.unlock();
        win.logMsg(QObject::tr("%1 UDP: Entities list already send to %2, resending anyway").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));
        //return;
    }
    else // Loading finished, sending entities list
    {
        win.logMsg(QObject::tr("%1 UDP: Sending entities list (npcs,mobs,etc.) to %2").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));
    }

    Scene* scene = findScene(player->pony.sceneName); // Spawn all the players on the client
    for (int i=0; i<scene->players.size(); i++)
        sendNetviewInstantiate(&scene->players[i]->pony,player);

    // Send NPCs
    for (int i=0; i<loe.npcs.size(); i++)
    {
        if (loe.npcs[i]->sceneName.toLower() == player->pony.sceneName.toLower())
        {
            win.logMsg(QObject::tr("%1 UDP: Sending NPC %2 to %3").arg(LOG_INFO).arg(loe.npcs[i]->name).arg(QString().setNum(player->pony.netviewId)));
            sendNetviewInstantiate(loe.npcs[i], player);
        }
    }

    // Send Mobs
    /*for (int i=0; i<loe.mobs.size(); i++)
    {
        if(loe.mobs[i]->sceneName.toLower() == player->pony.sceneName.toLower())
        {
            win.logMsg(QObject::tr("%1 UDP: Sending Mob %2 to %3").arg(LOG_INFO).arg(loe.mobs[i]->modelName).arg(QString().setNum(player->pony.netviewId)));
            sendNetviewInstantiate(player, loe.mobs[i]);
        }
    }*/

    // Mob debugging, comment if mob system works
    // Spawn some mobs in Zecoras
    //if (scene->name.toLower() == "zecoras")
    //{
          //sendNetviewInstantiate(player, "mobs/dragon", loe.getNewId(),loe.getNewNetviewId(), {-33.0408, 0.000425577, 101.766}, {0, -1,0,1});
    //}

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
    if (player->inGame < 2)
    {
        win.logMsg(QObject::tr("%1 UDP: Savegame requested too soon by %2").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));
        return;
    }

    quint16 netviewId = (quint8)msg[6] + ((quint8)(quint8)msg[7] << 8);
    Player* refreshPlayer = Player::findPlayer(loe.udpPlayers, netviewId);

    // If we find a matching NPC, send him and exits
    Pony* npc = NULL;
    for (int i=0; i<loe.npcs.size(); i++)
        if (loe.npcs[i]->netviewId == netviewId)
            npc = loe.npcs[i];

    if (npc != NULL)
    {
        win.logMsg(QObject::tr("%1 UDP: Sending ponyData and worn tiems for NPC %2").arg(LOG_INFO).arg(npc->name));
        sendPonyData(npc, player);

        if (npc->inv.size()) // If this npc has a shop
        {
            //sendAddViewAddShop(player, npc);
        }
        return;
    }

    // If we find a matching mob, sebd him and exits
    /*Mob* mob = nullptr;
    for (int i=0; i<loe.mobs.size(); i++)
    {
        if (loe.mobs[i]->netviewId == netviewId) mob = loe.mobs[i];
    }
    if (mob != nullptr)
    {
        // I'm not sure what we're supposed to send. Let's just return for the moment, it works.

        // -> We should probably send the mob's stats here
        //win.logMessage("[INFO] UDP: mob ponyData requested");
        sendSetMaxStatRPC(player, mob->netviewId, 1, defaultMaxHealth[(unsigned)mob->type]);
        sendSetMaxStatRPC(player, mob->netviewId, 1, mob->health);

        return;
    }*/

    if (netviewId == player->pony.netviewId) // Current player
    {
        if (player->inGame == 3) // Hopefully that'll fix people stuck on the default cam without creating clones
        {
            win.logMsg(QObject::tr("%1 UDP: Savegame already sent to %2, resending anyway").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));
        }
        else win.logMsg(QObject::tr("%1 UDP: Sending pony save data for %2").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));

        // Set current/max stats
        sendSetMaxStatRPC(player, 0, 100);
        sendSetStatRPC(player, 0, 100);
        sendSetMaxStatRPC(player, 1, 100);
        sendSetStatRPC(player, 1, 100);

        sendPonyData(player);

        // Send inventory
        sendInventoryRPC(player, player->pony.inv, player->pony.wornItm, player->pony.nBits);

        // Send Skills
        QList<QPair<quint32, quint32> > skills;
        if (Settings::lmmPlayer)
        {
            skills << QPair<quint32, quint32>(10, 0); // Ground Pound
            skills << QPair<quint32, quint32>(5, 0); // Seismic buck
            skills << QPair<quint32, quint32>(16, 0); // Rough Terrain
            skills << QPair<quint32, quint32>(11, 0); // Tornado
            skills << QPair<quint32, quint32>(14, 0); // Gale
            skills << QPair<quint32, quint32>(2, 0); // Teleport
            skills << QPair<quint32, quint32>(9, 0); // Rainbow Fields
            skills << QPair<quint32, quint32>(12, 0); // Heal
            skills << QPair<quint32, quint32>(15, 0); // Magical Arrow
            skills << QPair<quint32, quint32>(17, 0); // Fire Breath (dragons)
        }
        else
        {
            skills << QPair<quint32, quint32>(10, 0); // Ground Pound (All Races)
            if (player->pony.getType() == Pony::EarthPony)
            {
                skills << QPair<quint32, quint32>(5, 0); // Seismic buck
                skills << QPair<quint32, quint32>(16, 0); // Rough Terrain
            }
            else if (player->pony.getType() == Pony::Pegasus)
            {
                skills << QPair<quint32, quint32>(11, 0); // Tornado
                skills << QPair<quint32, quint32>(14, 0); // Gale
            }
            else if (player->pony.getType() == Pony::Unicorn)
            {
                skills << QPair<quint32, quint32>(2, 0); // Teleport
                skills << QPair<quint32, quint32>(9, 0); // Rainbow Fields
                skills << QPair<quint32, quint32>(12, 0); // Heal
                skills << QPair<quint32, quint32>(15, 0); // Magical Arrow
            }
        }
        sendSkillsRPC(player, skills);

        // Set current/max stats again (that's what the official server does, not my idea !)
        sendSetMaxStatRPC(player, 0, 100);
        sendSetStatRPC(player, 0, 100);
        sendSetMaxStatRPC(player, 1, 100);
        sendSetStatRPC(player, 1, 100);

        refreshPlayer->inGame = 3;
    }
    else if (!refreshPlayer->IP.isEmpty())
    {
        win.logMsg(QObject::tr("%1 UDP: Sending pony save data for %2").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));

        //sendWornRPC(refresh, player, refresh->worn);

        sendSetStatRPC(refreshPlayer, player, 0, 100);
        sendSetMaxStatRPC(refreshPlayer, player, 0, 100);
        sendSetStatRPC(refreshPlayer, player, 1, 100);
        sendSetMaxStatRPC(refreshPlayer, player, 1, 100);

        sendPonyData(&refreshPlayer->pony, player);

        if (!refreshPlayer->lastValidReceivedAnimation.isEmpty())
            sendMessage(player, MsgUserReliableOrdered12, refreshPlayer->lastValidReceivedAnimation);

    }
    else win.logMsg(QObject::tr("%1 UDP: Error sending pony save data! NetviewId: %2").arg(LOG_SEVERE).arg(QString().setNum(player->pony.netviewId)));
}

void sendNetviewInstantiate(Player *player, QString key, quint16 NetviewId, quint16 ViewId, UVector pos, UQuaternion rot)
{
    QByteArray data(1,1);
    data += stringToData(key);
    QByteArray data2(4,0);
    data2[0] = (quint8)(NetviewId & 0xFF);
    data2[1] = (quint8)((NetviewId >> 8) &0xFF);
    data2[2] = (quint8)(ViewId & 0xFF);
    data2[3] = (quint8)((ViewId >> 8) &0xFF);

    data += data2;
    data += vectorToData(pos);
    data += quaternionToData(rot);

    sendMessage(player, MsgUserReliableOrdered6, data);
}

/*void sendNetviewInstantiate(Player *player, Mob *mob)
{
    sendNetviewInstantiate(player, mob->modelName, mob->netviewId, mob->id, mob->pos, mob->rot);
}*/

void sendNetviewInstantiate(Player *player)
{
    win.logMsg(QObject::tr("%1 UDP: Send instantiate for/to %2").arg(LOG_INFO).arg(QString().setNum(player->pony.netviewId)));

    QByteArray data(1,1);
    data += stringToData("PlayerBase");
    QByteArray data2(4,0);
    data2[0] = (quint8)(player->pony.netviewId &0xFF);
    data2[1] = (quint8)((player->pony.netviewId >> 8) &0xFF);
    data2[2] = (quint8)(player->pony.id & 0xFF);
    data2[3] = (quint8)((player->pony.id >> 8) &0xFF);

    data += data2;
    data += vectorToData(player->pony.pos);
    data += quaternionToData(player->pony.rot);

    sendMessage(player, MsgUserReliableOrdered6, data);

    win.logMsg(QObject::tr("%1 UDP: Instantiate at %2 %3 %4").arg(LOG_INFO).arg(QString().setNum(player->pony.pos.x)).arg(QString().setNum(player->pony.pos.y)).arg(QString().setNum(player->pony.pos.z)));
}

void sendNetviewInstantiate(Pony *src, Player *dst)
{
    win.logMsg(QObject::tr("%1 UDP: Send instantiate for %2 to %3").arg(LOG_INFO).arg(QString().setNum(src->netviewId)).arg(QString().setNum(dst->pony.netviewId)));

    QByteArray data(1,1);
    data += stringToData("PlayerBase");
    QByteArray data2(4,0);
    data2[0] = (quint8)(src->netviewId &0xFF);
    data2[1] = (quint8)((src->netviewId >> 8) &0xFF);
    data2[2] = (quint8)(src->id & 0xFF);
    data2[3] = (quint8)((src->id >> 8) &0xFF);

    data += data2;
    data += vectorToData(src->pos);
    data += quaternionToData(src->rot);

    sendMessage(dst, MsgUserReliableOrdered6, data);

    //win.logMsg(QObject::tr("%1 UDP: Instantiate at %2 %3 %4").arg(LOG_INFO).arg(QString().setNum(rSrc.pony.pos.x)).arg(QString().setNum(rSrc.pony.pos.y)).arg(QString().setNum(rSrc.pony.pos.z)));
}

void sendNetviewRemove(Player *player, quint16 netviewId)
{
    win.logMsg(QObject::tr("%1 UDP: Removing netview %2 to %3").arg(LOG_INFO).arg(QString().setNum(netviewId)).arg(QString().setNum(player->pony.netviewId)));

    QByteArray data(3,2);
    data[1] = (quint8)(netviewId & 0xFF);
    data[2] = (quint8)((netviewId >> 8) &0xFF);
    sendMessage(player, MsgUserReliableOrdered6, data);
}

void sendNetviewRemove(Player *player, quint16 netviewId, quint8 reasonCode)
{
    win.logMsg(QObject::tr("%1 UDP: Removing netview %2 to %3. Reason Code: %4").arg(LOG_INFO).arg(QString().setNum(netviewId)).arg(QString().setNum(player->pony.netviewId)).arg(QString().setNum(reasonCode)));

    QByteArray data(4,2);
    data[1] = (quint8)(netviewId & 0xFF);
    data[2] = (quint8)((netviewId >> 8) &0xFF);
    data[3] = reasonCode;
    sendMessage(player, MsgUserReliableOrdered6, data);
}

void sendSetStatRPC(Player* player, quint16 netviewId, quint8 statId, float value)
{
    QByteArray data(4,50);
    data[0] = (quint8)(netviewId&0xFF);
    data[1] = (quint8)((netviewId>>8)&0xFF);
    data[3] = statId;
    data += floatToData(value);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendSetMaxStatRPC(Player* player, quint16 netviewId, quint8 statId, float value)
{
    QByteArray data(4,51);
    data[0] = (quint8)(netviewId&0xFF);
    data[1] = (quint8)((netviewId>>8)&0xFF);
    data[3] = statId;
    data += floatToData(value);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendSetStatRPC(Player *player, quint8 statId, float value)
{
    sendSetStatRPC(player, player->pony.netviewId, statId, value);
}

void sendSetMaxStatRPC(Player *player, quint8 statId, float value)
{
    sendSetMaxStatRPC(player, player->pony.netviewId, statId, value);
}

void sendSetStatRPC(Player* affected, Player* dest, quint8 statId, float value)
{
    QByteArray data(4,50);
    data[0] = (quint8)(affected->pony.netviewId&0xFF);
    data[1] = (quint8)((affected->pony.netviewId>>8)&0xFF);
    data[3] = statId;
    data += floatToData(value);
    sendMessage(dest, MsgUserReliableOrdered18, data);
}

void sendSetMaxStatRPC(Player* affected, Player* dest, quint8 statId, float value)
{
    QByteArray data(4,51);
    data[0] = (quint8)(affected->pony.netviewId&0xFF);
    data[1] = (quint8)((affected->pony.netviewId>>8)&0xFF);
    data[3] = statId;
    data += floatToData(value);
    sendMessage(dest, MsgUserReliableOrdered18, data);
}


void sendWornRPC(Player* player)
{
    sendWornRPC(player, player->pony.wornItm);
}

void sendWornRPC(Player *player, QList<WearableItem> &worn)
{
    QByteArray data(3, 4);
    data[0] = (quint8)(player->pony.netviewId&0xFF);
    data[1] = (quint8)((player->pony.netviewId>>8)&0xFF);
    data += 32; // Max Worn Items
    data += (uint8_t)worn.size();
    for (int i=0;i<worn.size();i++)
    {
        data += (quint8)((worn[i].index-1)&0xFF);
        data += (quint8)(worn[i].id&0xFF);
        data += (quint8)((worn[i].id>>8)&0xFF);
        data += (quint8)((worn[i].id>>16)&0xFF);
        data += (quint8)((worn[i].id>>24)&0xFF);
    }
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendWornRPC(Pony *wearing, Player *dest, QList<WearableItem> &worn)
{
    QByteArray data(3, 4);
    data[0] = (quint8)(wearing->netviewId&0xFF);
    data[1] = (quint8)((wearing->netviewId>>8)&0xFF);
    data += 32; // Max Worn Items
    data += worn.size();
    for (int i=0;i<worn.size();i++)
    {
        data += (quint8)((worn[i].index-1)&0xFF);
        data += (quint8)(worn[i].id&0xFF);
        data += (quint8)((worn[i].id>>8)&0xFF);
        data += (quint8)((worn[i].id>>16)&0xFF);
        data += (quint8)((worn[i].id>>24)&0xFF);
    }
    sendMessage(dest, MsgUserReliableOrdered18, data);
}

void sendInventoryRPC(Player* player)
{
    sendInventoryRPC(player, player->pony.inv, player->pony.wornItm, player->pony.nBits);
}

void sendInventoryRPC(Player *player, QList<InventoryItem>& inv, QList<WearableItem>& worn, quint32 nBits)
{
    QByteArray data(5, 5);
    data[0] = (quint8)(player->pony.netviewId & 0xFF);
    data[1] = (quint8)((player->pony.netviewId>>8) & 0xFF);
    data[3] = MAX_INVENTORY_SIZE; // Max Inventory Size
    data[4] = (quint8)inv.size();
    for (int i=0;i<inv.size();i++)
    {
        data += (quint8)inv[i].index;
        data += (quint8)(inv[i].id & 0xFF);
        data += (quint8)((inv[i].id>>8) & 0xFF);
        data += (quint8)((inv[i].id>>16) & 0xFF);
        data += (quint8)((inv[i].id>>24) & 0xFF);
        data += (quint8)(inv[i].amount & 0xFF);
        data += (quint8)((inv[i].amount>>8) & 0xFF);
        data += (quint8)((inv[i].amount>>16) & 0xFF);
        data += (quint8)((inv[i].amount>>24) & 0xFF);
    }
    data += MAX_WORN_ITEMS; // Max Worn Items
    data += worn.size();
    for (int i=0;i<worn.size();i++)
    {
        data += (quint8)worn[i].index-1;
        data += (quint8)(worn[i].id & 0xFF);
        data += (quint8)((worn[i].id>>8) & 0xFF);
        data += (quint8)((worn[i].id>>16) & 0xFF);
        data += (quint8)((worn[i].id>>24) & 0xFF);
    }
    data += (quint8)(nBits & 0xFF);
    data += (quint8)((nBits>>8) & 0xFF);
    data += (quint8)((nBits>>16) & 0xFF);
    data += (quint8)((nBits>>24) & 0xFF);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendSetBitsRPC(Player* player)
{
    QByteArray data(3, 0x10);
    data[0] = (quint8)(player->pony.netviewId & 0xFF);
    data[1] = (quint8)((player->pony.netviewId>>8) & 0xFF);
    data += uint32ToData(player->pony.nBits);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendSkillsRPC(Player *player, QList<QPair<quint32, quint32> > &skills)
{
#if USE_BABSCON_CLIENT
    QByteArray data(8, 0xC3);
#elif USE_BRONYCON_CLIENT
    QByteArray data(4, 0xC3);
#endif
    data[0] = (quint8)(player->pony.netviewId&0xFF);
    data[1] = (quint8)((player->pony.netviewId>>8)&0xFF);
    data[3] = 0x00; // Use dictionnary flag
#if USE_BABSCON_CLIENT
    data[4] = (quint8)(skills.size()&0xFF);
    data[5] = (quint8)((skills.size()>>8)&0xFF);
    data[6] = (quint8)((skills.size()>>16)&0xFF);
    data[7] = (quint8)((skills.size()>>24)&0xFF);
#endif
    for (int i=0; i<skills.size(); i++)
    {
        data += (quint8)(skills[i].first&0xFF);
        data += (quint8)((skills[i].first>>8)&0xFF);
        data += (quint8)((skills[i].first>>16)&0xFF);
        data += (quint8)((skills[i].first>>24)&0xFF);
        data += (quint8)(skills[i].second&0xFF);
        data += (quint8)((skills[i].second>>8)&0xFF);
        data += (quint8)((skills[i].second>>16)&0xFF);
        data += (quint8)((skills[i].second>>24)&0xFF);
    }
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendPonyData(Player *player)
{
    // Sends the ponyData
    //win.logMessage(QString("UDP: Sending the ponyData for/to "+QString().setNum(player->pony.netviewId)));
    QByteArray data(3,0xC8);
    data[0] = (quint8)(player->pony.netviewId&0xFF);
    data[1] = (quint8)((player->pony.netviewId>>8)&0xFF);
    data += player->pony.ponyData;
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendPonyData(Pony *src, Player *dst)
{
    // Sends the ponyData
    //win.logMessage(QString("UDP: Sending the ponyData for "+QString().setNum(src->pony.netviewId)
    //                       +" to "+QString().setNum(dst->pony.netviewId)));
    QByteArray data(3,0xC8);
    data[0] = (quint8)(src->netviewId&0xFF);
    data[1] = (quint8)((src->netviewId>>8)&0xFF);
    data += src->ponyData;
    sendMessage(dst, MsgUserReliableOrdered18, data);
}

void sendLoadSceneRPC(Player *player, QString sceneName) // Loads a scene and send to the default spawn
{
    win.logMsg(QObject::tr("%1 UDP: Loading scene \"%2\" on %3").arg(LOG_INFO).arg(sceneName).arg(QString().setNum(player->pony.netviewId)));

    Vortex vortex = findVortex(sceneName, 0);
    if (vortex.destName.isEmpty())
    {
        win.logMsg(QObject::tr("%1 UDP: Specified Scene not in vortex Database. Aborting scene load!").arg(LOG_ERROR));
        return;
    }

    Scene* scene = findScene(sceneName);
    Scene* oldScene = findScene(player->pony.sceneName);
    if (scene->name.isEmpty() || oldScene->name.isDetached())
    {
        win.logMsg(QObject::tr("%1 Can't find the specified scene or the old Scene the player is on. Aborting!").arg(LOG_ERROR));
        return;
    }

    // Update scene players
    //win.logMsg("[INFO] sendLoadSceneRPC(): locking");
    levelLoadMutex.lock();
    player->inGame = 1;
    player->pony.pos = vortex.destPos;
    player->pony.sceneName = sceneName.toLower();
    player->lastValidReceivedAnimation.clear(); // Changing scenes resets Animations
    Player::removePlayer(oldScene->players, player->IP, player->port);

    // Decided to keep this oldScene if statement to fix the infinite scene loading. ~WapaMario63
    // -> Didn't fix at all, the server keeps outputting "[INFO] Pong Received" all the time.
    // --> I believe this thing is from April or so, maybe near the time tux3 decide to toLowet() all scenenames.
    //if (oldScene->name.toLower() != sceneName.toLower())
      //{
    // Send remove RPC to the other players of the old scene
    for (int i=0; i<oldScene->players.size(); i++)
        sendNetviewRemove(oldScene->players[i], player->pony.netviewId);

    // Send instantiate to the players of the new scene
    for (int i=0; i<scene->players.size(); i++)
        if (scene->players[i]->inGame>=2)
            sendNetviewInstantiate(&player->pony, scene->players[i]);
      //}
    scene->players << player;

    QByteArray data(1,5);
    data += stringToData(sceneName.toLower());
    sendMessage(player, MsgUserReliableOrdered6, data); // Sends a 48
    //win.logMsg("[INFO] sendLoadSceneRPC(): unlocking");
    levelLoadMutex.unlock();
}

void sendLoadSceneRPC(Player* player, QString sceneName, UVector pos) // Loads a scene and send to the given pos
{
    win.logMsg(QString(QString("[INFO] UDP: Loading scene \"")+sceneName
                           +"\" to "+QString().setNum(player->pony.netviewId)
                           +" at "+QString().setNum(pos.x)+" "
                           +QString().setNum(pos.y)+" "
                           +QString().setNum(pos.z)));

    Scene* scene = findScene(sceneName);
    Scene* oldScene = findScene(player->pony.sceneName);
    if (scene->name.isEmpty() || oldScene->name.isEmpty())
    {
        win.logMsg("[ERROR] UDP: Can't find the scene, aborting");
        return;
    }

    // Update scene players
    //win.logMessage("sendLoadSceneRPC pos: locking");
    levelLoadMutex.lock();
    player->inGame=1;
    player->pony.pos = pos;
    player->pony.sceneName = sceneName.toLower();
    player->lastValidReceivedAnimation.clear(); // Changing scenes resets animations
    Player::removePlayer(oldScene->players, player->IP, player->port);

    // Decided to keep this oldScene if statement to fix the infinite scene loading. ~WapaMario63
    // -> Didn't fix at all, the server keeps outputting "[INFO] Pong Received" all the time.
    //if (oldScene->name.toLower() != sceneName.toLower())
      //{
    // Send remove RPC to the other players of the old scene
    for (int i=0; i<oldScene->players.size(); i++)
        sendNetviewRemove(oldScene->players[i], player->pony.netviewId);

    // Send instantiate to the players of the new scene
    for (int i=0; i<scene->players.size(); i++)
        if (scene->players[i]->inGame>=2)
            sendNetviewInstantiate(&player->pony, scene->players[i]);
      //}
    scene->players << player;

    QByteArray data(1,5);
    data += stringToData(sceneName.toLower());
    sendMessage(player,MsgUserReliableOrdered6,data); // Sends a 48
    //win.logMessage("sendLoadSceneRPC pos: unlocking");
    levelLoadMutex.unlock();
}

void sendChatMessage(Player *player, QString message, QString author, quint8 chatType)
{
    QByteArray idAndAccess(5,0);
    idAndAccess[0] = (quint8)(player->pony.netviewId & 0xFF);
    idAndAccess[1] = (quint8)((player->pony.netviewId << 8) &0xFF);
    idAndAccess[2] = (quint8)((player->pony.id & 0xFF));
    idAndAccess[3] = (quint8)((player->pony.id << 8) &0xFF);
    idAndAccess[4] = 0x0; // Access Level

    QByteArray data(2,0);
    data[0] = 0xF; // RPD ID for chat
    data[1] = chatType;

    data += stringToData(author);
#if USE_BRONYCON_CLIENT
    data += stringToData(author);
#endif
    data += stringToData(message);
    data += idAndAccess;
#if USE_BRONYCON_CLIENT
    data += uint32ToData(0); // Datetime
    data += uint32ToData(0); // Datetime
#endif

    sendMessage(player, MsgUserReliableOrdered4, data); // Sends a 46
}

void sendMove(Player *player, float x, float y, float z)
{
    QByteArray data(1,0);
    data[0] = 0xCE; // RPC ID for teleportation/moving of players

    data += floatToData(x);
    data += floatToData(y);
    data += floatToData(z);

    win.logMsg(QObject::tr("%1 UDP: Moving pony...").arg(LOG_INFO));
    sendMessage(player, MsgUserReliableOrdered4, data);
}

void sendBeginDialog(Player *player)
{
    QByteArray data(1,0);
    data[0] = 11; // RPC ID for NPC beginDialog (NPC text box init)
    sendMessage(player, MsgUserReliableOrdered4, data);
}

// NPC Message if the NPC has a show-accurate vector icon (example: Astral Charm) in place
void sendDialogMessage(Player *player, QString &message, QString NPCName, quint16 iconId)
{
    QByteArray data(1,0);
    data[0] = 0x11; // RPC ID for NPC text box message

    data += stringToData(message);
    data += stringToData(NPCName);
    data += (quint8)(iconId & 0xFF);
    data += (quint8)((iconId >> 8) &0xFF);

    sendMessage(player, MsgUserReliableOrdered4, data);
}

// NPC Message for the rest of NPCs with the 3D Model icons, this only applies if hasIconId is false.
void sendDialogMessage(Player *player, QString &message, QString NPCName, quint16 npc3DNetviewId, quint16 iconId)
{
    QByteArray data(1,0);
    data[0] = 0x11; // RPC ID for NPC text box message

    data += stringToData(message);
    data += stringToData(NPCName);
    data += uint16ToData(npc3DNetviewId);
    data += (quint8)(iconId & 0xFF);
    data += (quint8)((iconId >> 8) &0xFF);

    sendMessage(player, MsgUserReliableOrdered4, data);

}

void sendDialogOptions(Player *player, QList<QString> &answers)
{
    QByteArray data(5,0);
    data[0] = 0xC; // RPC ID for Dialog Selector (You know, when you have to choose a dialog to say to an NPC? Yeah those, it's the options).
    data[1] = (quint8)(answers.size() & 0xFF);
    data[2] = (quint8)((answers.size() >> 8) &0xFF);
    data[3] = (quint8)((answers.size() >> 16) &0xFF);
    data[4] = (quint8)((answers.size() >> 24) &0xFF);

    for (int i=0; i<answers.size(); i++) data += stringToData(answers[i]);

    sendMessage(player, MsgUserReliableOrdered4, data);
}

void sendEndDialog(Player *player)
{
    QByteArray data(1,0);
    data[0] = 13; // RPC ID for NPC endDialog (NPC Text box end/close)
    sendMessage(player, MsgUserReliableOrdered4, data);
}

void sendWearItemRPC(Player* player, const WearableItem& item)
{
    QByteArray data;
    data += uint16ToData(player->pony.netviewId);
    data += 0x8;
    data += uint32ToData(item.id);
    data += uint8ToData(item.index);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendWearItemRPC(Pony* wearing, Player* dest, const WearableItem& item)
{
    QByteArray data;
    data += uint16ToData(wearing->netviewId);
    data += 0x8;
    data += uint32ToData(item.id);
    data += uint8ToData(item.index);
    sendMessage(dest, MsgUserReliableOrdered18, data);
}

void sendUnwearItemRPC(Player* player, uint8_t slot)
{
    QByteArray data;
    data += uint16ToData(player->pony.netviewId);
    data += 0x9;
    data += uint8ToData(slot);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendUnwearItemRPC(Pony* wearing, Player* dest, uint8_t slot)
{
    QByteArray data;
    data += uint16ToData(wearing->netviewId);
    data += 0x9;
    data += uint8ToData(slot);
    sendMessage(dest, MsgUserReliableOrdered18, data);
}

void sendAddItemRPC(Player* player, const InventoryItem& item)
{
    QByteArray data;
    data += uint16ToData(player->pony.netviewId);
    data += 0x6;
    data += uint32ToData(item.id);
    data += uint32ToData(item.amount);
    data += uint32ToData(item.index);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendDeleteItemRPC(Player* player, uint8_t index, uint32_t qty)
{
    QByteArray data;
    data += uint16ToData(player->pony.netviewId);
    data += 0x7;
    data += uint8ToData(index);
    data += uint32ToData(qty);
    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendAddViewAddShop(Player *player, Pony *npcShop)
{
    QByteArray data;
    data += 0x0A; // RPC ID for AddView
    data += uint16ToData(npcShop->netviewId);
    data += uint16ToData(npcShop->netviewId);
    //data += uint16ToData(player->pony.netviewId);
    data += stringToData("AddShop");

    sendMessage(player, MsgUserReliableOrdered6, data);
}

void sendBeginShop(Player* player, Pony* npcShop)
{
    QByteArray data;
    data += uint16ToData(npcShop->netviewId);
    data += 0x16; // RPC ID for Shop init

    data += uint32ToData(npcShop->inv.size());

    for (const InventoryItem& item : npcShop->inv)
    {
        data += uint32ToData(item.id);
        data += uint32ToData(item.amount);
    }
    data += stringToData("Wearable Items"); // Shop name, affects all shops, for now.

    sendMessage(player, MsgUserReliableOrdered18, data);
}

void sendEndShop(Player* player)
{
    QByteArray data;
    data += uint16ToData(player->pony.netviewId);
    data += 0x17; // RPC ID for Shop End

    sendMessage(player, MsgUserReliableOrdered18, data);
}

/*void sendAnimation(Player *player, const Animation *animation)
{
    QByteArray data;
    data += uint16ToData(player->pony.netviewId);
    data += 0xCA; // Animation
    data += uint32ToData(animation->id);

    sendMessage(player, MsgUserReliableOrdered12, data);
}*/

void sendAnnouncementMessage(Player *player, QString message, float time)
{
    QByteArray data(1,0);
    data[0] = 0xC9; // RPC ID for Announcement box and Red Text

    data += stringToData(message);
    data += floatToData(time);

    sendMessage(player, MsgUserReliableOrdered4, data);
}

void sendMessageBox(Player *player, QString msg)
{
    QByteArray data(1,0);
    data[0] = 0x7F; // RPC ID for message box
    data += stringToData(msg);
    sendMessage(player, MsgUserReliableOrdered4, data);
}
