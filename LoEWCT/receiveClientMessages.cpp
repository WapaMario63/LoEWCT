#include "message.h"
#include "player.h"
#include "pony.h"
#include "loewct.h"
#include "mainwindow.h"
#include "sync.h"
#include "utils.h"
#include "serialize.h"
#include "receiveClientAck.h"
#include "chat.h"
//#include "mob.h"
//#include "packetloss.h"
//#include "skill.h"
#include "settings.h"

void receiveMessage(Player *player)
{
    QSettings loewctconfig(LOEWCTCONFIGFILEPATH, QSettings::IniFormat);
    Settings::serverPrefix = loewctconfig.value("serverPrefix", "[LoEWCT]").toString();
    Settings::pvp = loewctconfig.value("pvp", false).toBool();
    Settings::playerJoingMsg = loewctconfig.value("playerJoined", true).toBool();
    Settings::maxPacketDups = loewctconfig.value("maxPacketDups", 100).toUInt();

    QByteArray msg = *(player->receivedDatas);
    int msgSize = 5 + (((unsigned char)msg[3]) + (((unsigned char)msg[4]) << 8)) / 8;

#if UDP_SIMULATE_PACKETLOSS
    if (qrand() % 100 <= UDP_RECV_PERCENT_DROPPED)
    {
        //win.logMessage("UDP: Received packet dropped !");
        *(player->receivedDatas) = player->receivedDatas->mid(msgSize);
        if (player->receivedDatas->size())
            receiveMessage(player);
        return; // When we're done with the recursion, we still need to skip this message.
    }
    else
    {
        //win.logMessage("UDP: Received packet got through !");
    }
#endif
    // Check the sequence (seq) of the received message
    if ((unsigned char)msg[0] >= MsgUserReliableOrdered1 && (unsigned char)msg[0] <= MsgUserReliableOrdered32)
    {
        quint16 seq = (quint8)msg[1] + ((quint8)msg[2] << 8);
        quint8 channel = ((unsigned char)msg[0]) - MsgUserReliableOrdered1;
        if (seq <= player->udpRecvSequenceNumbers[channel] && player->udpRecvSequenceNumbers[channel] != 0)
        {
            // If this is a missing packet, accept it
            MessageHead missingMsg;
            missingMsg.channel = channel;
            missingMsg.seq = seq;
            if (player->udpRecvMissing.contains(missingMsg))
            {
                win.logMsg(QObject::tr("%1 UDP: Processing retransmission (-%2) from %3").arg(LOG_INFO).arg(QString().setNum(player->udpRecvSequenceNumbers[channel]-seq)).arg(QString().setNum(player->pony.netviewId)));
                for (int i=0; i<player->udpRecvMissing.size(); i++)
                {
                    if (player->udpRecvMissing[i] == missingMsg)
                        player->udpRecvMissing.remove(i);
                }
            }
            else
            {
                // We already processed this packet, we should discard it
                win.logMsg(QObject::tr("%1 UDP: Discarding double message (-%2) from %3").arg(LOG_INFO).arg(QString().setNum(player->udpRecvSequenceNumbers[channel]-seq)).arg(QString().setNum(player->pony.netviewId)));
                win.logMsg(QObject::tr("%1 UDP: Message was: %2").arg(LOG_INFO).arg(player->receivedDatas->left(msgSize).toHex().data()));
                player->nReceivedDups++;
                if (player->nReceivedDups >= Settings::maxPacketDups) // Kick the player if he's infinite-looping on us
                {
                    win.logMsg(QObject::tr("%1 UDP: Kicking %2 from server. Reason: Too Many Packet Dups (Lagging the Server)"));
                    sendMessage(player, MsgDisconnect, "Kicked by Server \nReason \n-------------------------------\n Lagging the server (too many packet dups)");
                    Player::disconnectPlayerCleanUp(player); // Save game and remove the player
                    return;
                }
                *(player->receivedDatas) = player->receivedDatas->mid(msgSize);

                // Ack if needed, so that the client knows to move on already
                if ((unsigned char)msg[0] >= MsgUserReliableOrdered1 && (unsigned char)msg[0] < MsgUserReliableOrdered32) // User Reliable ordered
                {
                    //win.logMsg("[INFO] UDP: ACKing discarded Message");
                    QByteArray data(3,0);
                    data[0] = (quint8)(msg[0]); // ack type
                    data[1] = (quint8)(((quint8)msg[1]) / 2); // seq
                    data[2] = (quint8)(((quint8)msg[2]) / 2); // seq
                    sendMessage(player, MsgAcknowledge, data);
                }

                if (player->receivedDatas->size()) receiveMessage(player);
                return; // When we're done with the recursioon, we still need to skip this message.
            }
        }
        else if (seq > player->udpRecvSequenceNumbers[channel]+2) // If a message was skipped, keep going
        {
            win.logMsg(QObject::tr("%1 UDP: Unordered message (+%2) received from $3").arg(LOG_INFO).arg(seq - player->udpRecvSequenceNumbers[channel]).arg(QString().setNum(player->pony.netviewId)));
            player->udpRecvSequenceNumbers[channel] = seq;

            // Mark the packets we skipped as missing
            for (int i=player->udpRecvSequenceNumbers[channel]+2; i<seq; i+=2)
            {
                MessageHead missing;
                missing.channel = channel;
                missing.seq = i;
                player->udpRecvMissing.append(missing);
            }
        }
        else
        {
            if (player->nReceivedDups > 0) player->nReceivedDups--; // If we stopped sending dups, forgive him slowly
            player->udpRecvSequenceNumbers[channel] = seq;
        }
    }

    // Process the received message
    if ((unsigned char)msg[0] == MsgPing) // Ping
    {
        player->lastPingNumber = (quint8)msg[5];
        player->lastPingTime = timestampNow();
        sendMessage(player, MsgPing);
    }
    else if ((unsigned char)msg[0] == MsgPong) // Pong
    {
        win.logMsg(QObject::tr("%1 UDP: Pong received").arg(LOG_INFO));
    }
    else if ((unsigned char)msg[0] == MsgConnect) // Connect SYN
    {
        msg.resize(18); // Supprime le message LocalHail et le Timestamp (I belive this is french, >tfw don't know enough french to understand this)
        msg = msg.right(13); // Supprime le Header (same here)

        //win.logMsg("[INFO] Connecting...");

        for (int i=0; i<32; i++) player->udpSequenceNumbers[i] = 0; // Reset Sequence Numbers
        if (!player->isConnected) sendMessage(player, MsgConnectResponse, msg);
    }
    else if ((unsigned char)msg[0] == MsgConnectionEstablished) // Connect ACK
    {
        if (player->isConnected) win.logMsg(QObject::tr("%1 UDP: Received suplicated connect ACK").arg(LOG_INFO));
        else
        {
            win.logMsg(QObject::tr("%1 UDP: Connected to client").arg(LOG_INFO));
            player->isConnected = true;
            for (int i=0; i<32; i++) player->udpSequenceNumbers[i] = 0; // Reset Sequence Numbers

            onConnectAckReceived(player); // Clean the reliable message queue from SYN|ACKs

            // Start game

            //win.logMsg(LOG_INFO+"UDP: Starting Game");

            // Set local player id
            loe.lastIdMutex.lock();
            player->pony.id = loe.getNewId();
            player->pony.netviewId = loe.getNewNetviewId();
            loe.lastIdMutex.unlock();

            win.logMsg("[INFO] UDP: Set id request:"+ QString().setNum(player->pony.id) +"/"+ QString().setNum(player->pony.netviewId));

            QByteArray id(3,0); // Set player Id request
            id[0] = 4;
            id[1] = (quint8)(player->pony.id &0xFF);
            id[2] = (quint8)((player->pony.id >> 8) &0xFF);
            sendMessage(player, MsgUserReliableOrdered6, id); // Sends a 48

            // Load Character Select Screen Request
            QByteArray data(1,5);
            data += stringToData("Characters");
            sendMessage(player, MsgUserReliableOrdered6, data); // Sends a 48
        }
    }
    else if ((unsigned char)msg[0] == MsgAcknowledge) // Acknowledge
    {
        onAckReceived(msg, player);

        win.logMsg("[INFO] UDP: "+player->name+" disconnected.");
        Player::disconnectPlayerCleanUp(player); // Save game and remove the player

        if (Settings::playerJoingMsg)
        {
            for (int i=0; i<loe.udpPlayers.size(); i++)
                sendChatMessage(loe.udpPlayers[i], "<span color=\"yellow\">"+player->pony.name+" ("+player->name+") left the game.</span>", Settings::serverPrefix, ChatSystem);
        }

        return; // We can't use Player& player anymore, it refers to free'd memory
    }
    else if ((unsigned char)msg[0] >= MsgUserReliableOrdered1 && (unsigned char)msg[0] <= MsgUserReliableOrdered32) // User Reliable Ordered
    {
        //win.logMsg("UDP: Data received (hex) : ");
        //win.logMsg(player->receivedDatas->toHex() : \n"+player->receivedDatas->toHex().constData());

        QByteArray data(3,0);
        data[0] = (quint8)msg[0]; // ack type
        data[1] = (quint8)(((quint8)msg[1])/2); // seq
        data[2] = (quint8)(((quint8)msg[2])/2); // seq
        sendMessage(player, MsgAcknowledge, data);

        if ((unsigned char)msg[0] == MsgUserReliableOrdered6 && (unsigned char)msg[3] == 8 && (unsigned char)msg[4] == 0 && (unsigned char)msg[5] == 6) // Prefab (player/mobs) list instantiate request
        {
            sendEntitiesList(player); // Called when the level was loaded on the client side
        }
        else if ((unsigned char)msg[0]==MsgUserReliableOrdered6 && (unsigned char)msg[3]==0x18 && (unsigned char)msg[4]==0 && (unsigned char)msg[5]==8 ) // Player game info (inv/ponyData/...) request
        {
            sendPonySave(player, msg); // Called when instantiate finished on the client side
        }
        else if ((unsigned char)msg[0]==MsgUserReliableOrdered4 && (unsigned char)msg[5]==0xf) // Chat
        {
            receiveChatMessage(msg, player);
        }
        else if ((quint8)msg[0] == MsgUserReliableOrdered4 && (quint8)msg[5]==0x1 && player->inGame != 0) // Edit ponies request error
        {
            win.logMsg("[INFO] UDP: Rejecting game start request from "+QString().setNum(player->pony.netviewId)+". Player might be already in-game or an error happened on the character select screen of this player.");
            // Fix the buggy state we are now in
            // Reload to hide the "Saving Ponies..." message box
            QByteArray data(1,5);
            data += stringToData(player->pony.sceneName);
            sendMessage(player, MsgUserReliableOrdered6, data);
            // Try to cancel the loading callbacks with inGame = 1
            player->inGame = 1;
        }
        else if ((quint8)msg[0] == MsgUserReliableOrdered4 && (quint8)msg[5]==0x1 && player->inGame == 0) // Edit ponies request success
        {
            QList<Pony> ponies = Player::loadPonies(player);
            QByteArray ponyData = msg.right(msg.size()-10);
            win.logMsg("[INFO] ponyData size: "+ponyData.size());
            Pony pony{player};

#if USE_BRONYCON_CLIENT
            // fix invalid names (August Build)
            QString ponyName = dataToString(ponyData);
            if (ponyName.count(' ') > 1)
            {
                QStringList words = ponyName.split(' ');
                ponyName = words[0] + ' ' + words[1];
            }
#endif
            // New pony request
            if ((unsigned char)msg[6]==0xFF && (unsigned char)msg[7]==0xFF && (unsigned char)msg[8]==0xFF && (unsigned char)msg[9]==0xFF)
            {
                // Create the new pony for this player
                pony.ponyData;
                pony.name = dataToString(ponyData);
                pony.sceneName = "ponyville";
                pony.pos = findVortex(pony.sceneName, 0).destPos;
                ponies += pony;
            }
            else // If there is already a pony created
            {
                quint32 id = (quint8)msg[6] + ((quint8)msg[7] << 8) + ((quint8)msg[8] << 16) + ((quint8)msg[9] << 24);
                if (ponies.size() < 0 || (quint32)ponies.size() <= id)
                {
                    win.logMsg("[INFO] UDP: Reveived invalid ID in 'edit ponies' request, kicking the player.");
                    sendMessage(player, MsgDisconnect, "Kicked by Server \nReason \n-------------------------------\nFor sending invalid data and/or trying to crash the server with pony-id overflows.\nThis might be caused by an invalid pony name, so change it now.");
                    Player::disconnectPlayerCleanUp(player); // Save game and remove the player
                    return; // It's oj, since we just disconnected the player
                }
                ponies[id].ponyData = ponyData;
                pony = ponies[id];
            }
            pony.id = player->pony.id;
            pony.netviewId = player->pony.netviewId;
            player->pony = pony;

            Player::savePonies(player, ponies);

            player->pony.loadQuests();
            if (!player->pony.loadInventory()) // New Pony, send default inventory
            {
                player->pony.nBits = 15;
                player->pony.saveInventory();
            }

            sendLoadSceneRPC(player, player->pony.sceneName, player->pony.pos);

            // Send instantiate to the players of the new scene
            Scene* scene = findScene(player->pony.sceneName);
            for (int i=0; i<scene->players.size(); i++)
                if (scene->players[i]->pony.netviewId!=player->pony.netviewId && scene->players[i]->inGame>=2)
                    sendNetviewInstantiate(&player->pony, scene->players[i]);

            // Send the 46s init messages
            sendMessage(player, MsgUserReliableOrdered4, QByteArray::fromHex("141500000000")); // Send a 46, init friends
            sendMessage(player, MsgUserReliableOrdered4, QByteArray::fromHex("0e00000000")); // Sends a 46, init journal

            // Tell everyone that someone joined, if it's enabled of course
            if (Settings::playerJoingMsg)
            {
                for (int i=0; i<loe.udpPlayers.size(); i++)
                {
                    sendChatMessage(loe.udpPlayers[i], "<span color=\"yellow\">"+player->pony.name+" ("+player->name+") joined the game.</span>", Settings::serverPrefix, ChatSystem);
                }
            }
        }
        else if ((unsigned char)msg[0] == MsgUserReliableOrdered20 && (unsigned char)msg[3]==0x18 && (unsigned char)msg[4]==0) // Vortex Messages
        {
            if (player->inGame >= 2)
            {
                quint8 id = (quint8)msg[5];
                Vortex vortex = findVortex(player->pony.sceneName, id);
                if (vortex.destName.isEmpty())
                {
                    win.logMsg("[ERROR] Can't find vortex "+QString().setNum(id)+" on scene "+player->pony.sceneName);
                }
                else sendLoadSceneRPC(player, vortex.destName, vortex.destPos);
            }
        }
    }
}
