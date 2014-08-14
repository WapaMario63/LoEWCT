#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QMutex>
#include <QByteArray>
#include <QStringList>

#include "datatype.h"

// This file is like the most complicated one.
// Ehem, this file acesses a lot of the game's functions so the server can use them.

// Hacky at best indeed.

// This one... something related to player's stats/state
enum NetviewRemoveReasonCodes
{
    NetviewRemoveReasonDefault = 0,
    NetviewRemoveReasonKill = 1
};

// All of the game's message types.
enum MessageTypes
{
    MsgUnconnected = 0,
    MsgUserUnreliable = 1,
    MsgPing = 0x81,
    MsgPong = 0x82,
    MsgConnect = 0x83,
    MsgConnectResponse = 0x84,
    MsgConnectionEstablished = 0x85,
    MsgAcknowledge = 0x86,
    MsgDisconnect = 0x87,

    MsgUserReliableOrdered1 = 0x43,
    MsgUserReliableOrdered2 = 0x44,
    MsgUserReliableOrdered3 = 0x45,
    MsgUserReliableOrdered4 = 0x46,
    MsgUserReliableOrdered5 = 0x47,
    MsgUserReliableOrdered6 = 0x48,
    MsgUserReliableOrdered11 = 0x4d,
    MsgUserReliableOrdered12 = 0x4e,
    MsgUserReliableOrdered18 = 0x54,
    MsgUserReliableOrdered20 = 0x56,
    MsgUserReliableOrdered32 = 0x62
};

// Chat Types, you know, those tabs like Global, Local, etc.
enum ChatType
{
    ChatNone = 0,
    ChatUntyped = 1,
    ChatSystem = 2, // It's the [Announcement] from the official servers, but no [Announcement] on it, only that pen
    ChatGeneral = 4, // Global Chat
    ChatLocal = 8, // Says it all
    ChatParty = 16, // Says it all
    ChatGuild = 32, // Herd Chat
    ChatWhisper = 64 // Says it all
};

class Player;
class Pony;
//class Mob;
//class Animation;

// All the message functions.

/// Only in receiveMessage.cpp
void receiveMessage(Player* player);

/// Only in sendMessage.cpp
void sendMessage(Player* player, quint8 messageType, QByteArray data=QByteArray());

// Only in message.cpp
void sendEntitiesList(Player* player);
void sendPonySave(Player* player);
void sendPonies(Player* player);
void sendPonyData(Player* player);
void sendPonyData(Pony *src, Player* data);
void sendNetviewInstantiate(Player* player, QString key, quint16 NetviewId, quint16 viewId, UVector pos, UQuaternion rot);
void sendNetviewInstantiate(Player* player);
void sendNetviewInstantiate(Player* player, Mob* mob);
void sendNetviewInstantiate(Pony *src, Player* dst);
void sendNetviewRemove(Player* player, quint16 netviewId);
void sendNetviewRemove(Player* player, quint16 netviewId, quint8 reasonCode);
void sendSetStatRPC(Player* player, quint16 netviewId, quint8 statId, float value);
void sendSetMaxStatRPC(Player* player, quint16 netviewId, quint8 statId, float value);
void sendSetStatRPC(Player* player, quint8 statId, float value);
void sendSetMaxStatRPC(Player* player, quint8 statId, float value);
void sendSetStatRPC(Player* affected, Player* dest, quint8 statId, float value); // Set stat of affected on client dest
void sendSetMaxStatRPC(Player* affected, Player* dest, quint8 statId, float value); // Set stat of affected on client dest
void sendWornRPC(Player* player, QList<WearableItem>& worn); // Send items worn by player to himself
void sendWornRPC(Player* player); // Send items worn by player to himself
void sendWornRPC(Pony *wearing, Player* dest, QList<WearableItem>& worn); // Send items worn by wearing to dest
void sendWearItemRPC(Pony* wearing, Player* dest, const WearableItem& item); // Wear this item
void sendWearItemRPC(Player* player, const WearableItem& item); // Wear this item
void sendUnwearItemRPC(Player* player, uint8_t slot); // Unwear this item
void sendUnwearItemRPC(Pony* wearing, Player* dest, uint8_t slot); // Unwear this item
void sendInventoryRPC(Player* player, QList<InventoryItem>& inv, QList<WearableItem>& worn, quint32 nBits);
void sendInventoryRPC(Player* player);
void sendSetBitsRPC(Player* player); // Resend how many bits we have to the clients
void sendSkillsRPC(Player* player, QList<QPair<quint32, quint32> >& skills);
void sendLoadSceneRPC(Player* player, QString sceneName);
void sendLoadSceneRPC(Player* player, QString sceneName, UVector pos);
void sendChatMessage(Player* player, QString message, QString author, quint8 chatType);
void sendMove(Player* player, float x, float y, float z);
void sendBeginDialog(Player* player);
void sendDialogMessage(Player* player, QString& message, QString NPCName, quint16 iconId=0);
void sendDialogMessage(Player *player, QString &message, QString NPCName, quint16 npc3DNetviewId, quint16 iconId);
void sendDialogOptions(Player* player, QList<QString> &answers);
void sendEndDialog(Player* player);
void sendAddItemRPC(Player* player, const InventoryItem& item);
void sendDeleteItemRPC(Player* player, uint8_t index, uint32_t qty);
void sendBeginShop(Player* player, Pony* npcShop);
void sendEndShop(Player* player);
void sendAddViewAddShop(Player* player, Pony* npcShop);
void sendAnimation(Player* player, const Animation* animation);

#endif // MESSAGE_H
