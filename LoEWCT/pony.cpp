#include <QFile>
#include <QDir>

#include "pony.h"
#include "mainwindow.h"
#include "loewct.h"
#include "player.h"
#include "utils.h"
#include "serialize.h"
#include "message.h"
#include "sendMessage.h"
#include "settings.h"
//#include "items.h"
//#include "packetloss.h"

SceneEntity::SceneEntity()
{
    modelName = QString();
    id = 0;
    netviewId = 0;
    pos = UVector(0,0,0);
    rot = UQuaternion(0,0,0,0);
    sceneName = QString();
}

Pony::Pony(Player *Owner)
    : SceneEntity(), StatsComponent(), owner(Owner), dead{false},
      maxHealth{100}, defense{2.0}
{
    modelName = "PlayerBase";
    name = "";
    wornSlots = 0;
    health = maxHealth;
}

Pony::type Pony::getType()
{
    unsigned char num3; // Variable UInt32
    int num = 0;
    int num2 = 0;
    int i=0;
    do
    {
        num3 = ponyData[i]; i++;
        num |= (num3 & 0x7f) << num2;
        num2 += 7;
    } while ((num3 & 0x80) != 0);
    unsigned off = (uint) num + i;
    return (type)(quint8)ponyData[off];
}

void Pony::saveQuests()
{
    /*win.logMsg(QObject::tr("%1 UDP: Saving quests for %2 (%3)").arg(LOG_INFO).arg(QString().setNum(netviewId)).arg(owner->name));

    QDir playerPath(QDir::currentPath());
    playerPath.cd("data");
    playerPath.cd("players");
    playerPath.mkdir(owner->name.toLatin1());

    QFile file(QDir::currentPath()+"/data/players/"+owner->name.toLatin1()+"/quest.lpd");
    if (!file.open(QIODevice::ReadWrite))
    {
        win.logMsg(QObject::tr("%1 Error saving quests for %2 (%3)").arg(LOG_SEVERE).arg(QString().setNum(netviewId)).arg(owner->name));
        return;
    }
    QByteArray questData = file.readAll();

    // Try to find an existing entry for this pony, if found delete it. Then go at the end.
    for (int i=0; i<questData.size();)
    {
        // Read the name
        QString entryName = dataToString(questData.mid(i));
        int nameSize = entryName.size() + getVUint32Size(questData.mid(i));
        //win.logMsg("saveQuests : Reading entry "+entryName);

        quint16 entryDataSize = 4 * dataToUint16(questData.mid(i + nameSize));
        if (entryName == this->name) // Delete the entry, we'll reqrite it at the end
        {
            questData.remove(i, nameSize + entryDataSize + 2);
            break;
        }
        else i += nameSize + entryDataSize + 2;
    }

    // Now add out data at the end of the file
    QByteArray newEntry = stringToData(this->name);
    newEntry += (quint8)(quests.size() & 0xFF);
    newEntry += (quint8)((quests.size() >> 8) & 0xFF);
    for (const Quest& quest : quests)
    {
        newEntry += (quint8)(quest.id & 0xFF);
        newEntry += (quint8)((quest.id >> 8) & 0xFF);
        newEntry += (quint8)(quest.state & 0xFF);
        newEntry += (quint8)((quest.state >> 8) & 0xFF);
    }
    questData += newEntry;
    file.resize(0);
    file.write(questData);
    file.close();*/
}

void Pony::loadQuests()
{
    /*win.logMsg(QObject::tr("%1 UDP: Loading quests for %2 (%3)").arg(LOG_INFO).arg(QString().setNum(netviewId)).arg(owner->name));

    QDir playerPath(QDir::currentPath());
    playerPath.cd("data");
    playerPath.cd("players");
    playerPath.mkdir(owner->name.toLatin1());

    QFile file(QDir::currentPath()+"/data/players/"+owner->name.toLatin1()+"/quests.lpd");
    if (!file.open(QIODevice::ReadOnly))
    {
        win.logMsg(QObject::tr("%1 UDP: Error loading quests for %2 (%3)").arg(LOG_SEVERE).arg(QString().setNum(netviewId)).arg(owner->name));
        return;
    }
    QByteArray questData = file.readAll();
    file.close();

    // Try to find an existing entry for this pony and load it.
    for (int i=0; i<questData.size();)
    {
        // Read the name
        QString entryName = dataToString(questData.mid(i));
        int nameSize = entryName.size()+getVUint32Size(questData.mid(i));
        i+=nameSize;
        //win.logMessage("loadQuests : Reading entry "+entryName);

        quint16 nquests = dataToUint16(questData.mid(i));
        i+=2;
        if (entryName == this->name) // Read the entry
        {
            for (int j=0; j<nquests; j++)
            {
                quint16 questId = dataToUint16(questData.mid(i));
                quint16 questState = dataToUint16(questData.mid(i+2));
                i+=4;
                for (Quest& quest : quests)
                {
                    if (quest.id == questId)
                    {
                        quest.state = questState;
                        break;
                    }
                }
            }
            return;
        }
        else
            i += nquests * 4;
    }*/
}

void Pony::saveInventory()
{
    win.logMsg(QObject::tr("%1 UDP: Saving Inventory for %2 (%3)").arg(LOG_INFO).arg(QString().setNum(netviewId)).arg(owner->name));

    QDir playerPath(QDir::currentPath());
    playerPath.cd("data");
    playerPath.cd("players");
    playerPath.mkdir(owner->name.toLatin1());

    QFile file(QDir::currentPath()+"/data/players/"+owner->name.toLatin1()+"/inventory.lpd");
    if (!file.open(QIODevice::ReadWrite))
    {
        win.logMsg(QObject::tr("%1 UDP: Error Saving Inventory for %2 (%3)").arg(LOG_SEVERE).arg(QString().setNum(netviewId)).arg(owner->name));
        return;
    }
    QByteArray invData = file.readAll();

    // Try to find an existing entry for this pony, if found delete it. Then go at the end.
    for (int i=0; i<invData.size();)
    {
        // Read the name
        QString entryName = dataToString(invData.mid(i));
        int nameSize = entryName.size()+getVUint32Size(invData.mid(i));
        //win.logMessage("saveInventory : Reading entry "+entryName);

        quint8 invSize = invData[i+nameSize+4];
        quint8 wornSize = invData[i+nameSize+4+1+invSize*9]; // Serialized sizeof InventoryItem is 9
        if (entryName == this->name) // Delete the entry, we'll rewrite it at the end
        {
            invData.remove(i,nameSize+4+1+invSize*9+1+wornSize*5);
            break;
        }
        else // Skip this entry
            i += nameSize+4+1+invSize*9+1+wornSize*5;
    }

    // Now add our data at the end of the file
    QByteArray newEntry = stringToData(this->name);
    newEntry += uint32ToData(nBits);
    newEntry += uint8ToData(inv.size());
    for (const InventoryItem& item : inv)
    {
        newEntry += uint8ToData(item.index);
        newEntry += uint32ToData(item.id);
        newEntry += uint32ToData(item.amount);
    }
    newEntry += uint8ToData(wornItm.size());
    for (const WearableItem& item : wornItm)
    {
        newEntry += uint8ToData(item.index);
        newEntry += uint32ToData(item.id);
    }
    invData += newEntry;
    file.resize(0);
    file.write(invData);
    file.close();
}

bool Pony::loadInventory()
{
    win.logMsg(QObject::tr("%1 UDP: Loading Inventory for %2 (%3)").arg(LOG_INFO).arg(QString().setNum(netviewId)).arg(owner->name));

    QDir playerPath(QDir::currentPath());
    playerPath.cd("data");
    playerPath.cd("players");
    playerPath.mkdir(owner->name.toLatin1());

    QFile file(QDir::currentPath()+"/data/players/"+owner->name.toLatin1()+"/inventory.lpd");
    if (!file.open(QIODevice::ReadOnly))
    {
        win.logMsg(QObject::tr("%1 UDP: Error Loading Inventory for %2 (%3)").arg(LOG_SEVERE).arg(QString().setNum(netviewId)).arg(owner->name));
        return false;
    }
    QByteArray invData = file.readAll();
    file.close();

    // Try to find an existing entry for this pony, if found load it.
    for (int i=0; i<invData.size();)
    {
        // Read the name
        QString entryName = dataToString(invData.mid(i));
        int nameSize = entryName.size()+getVUint32Size(invData.mid(i));
        //win.logMessage("loadInventory : Reading entry "+entryName);

        quint8 invSize = invData[i+nameSize+4];
        quint8 wornSize = invData[i+nameSize+4+1+invSize*9]; // Serialized sizeof InventoryItem is 9
        if (entryName == this->name)
        {
            i += nameSize;
            nBits = dataToUint32(invData.mid(i));
            i+=5; // Skip nBits and invSize
            inv.clear();
            for (int j=0; j<invSize; j++)
            {
                InventoryItem item;
                item.index = invData[i];
                i++;
                item.id = dataToUint32(invData.mid(i));
                i+=4;
                item.amount = dataToUint32(invData.mid(i));
                i+=4;
                inv.append(item);
            }
            i++; // Skip wornSize
            wornItm.clear();
            wornSlots = 0;
            for (int j=0; j<wornSize; j++)
            {
                WearableItem item;
                item.index = invData[i];
                i++;
                item.id = dataToUint32(invData.mid(i));
                i+=4;
                wornItm.append(item);
                wornSlots |= loe.wearablePositionsMap[item.id];
            }
            return true;
        }
        else // Skip this entry
            i += nameSize+4+1+invSize*9+1+wornSize*5;
    }
    return false; // Entry not found
}

void Pony::addInventoryItem(quint32 id, quint32 qty)
{
    bool found=false;
    int firstFreeIndex=0;
    while (!found && firstFreeIndex < MAX_INVENTORY_SIZE)
    {
        found=true;
        for (InventoryItem& item : inv)
        {
            if (item.id == id)
            {
                item.amount += qty;
                sendAddItemRPC(owner, item);
                return;
            }
            else if (item.index == firstFreeIndex)
            {
                found=false;
                firstFreeIndex++;
                break;
            }
        }
    }
    if (!found)
        return;
    InventoryItem newItem(firstFreeIndex, id, qty);
    inv << newItem;
    sendAddItemRPC(owner, newItem);
}

void Pony::removeInventoryItem(quint32 id, quint32 qty)
{
    for (int i=0; i<inv.size(); i++)
    {
        if (inv[i].id == id)
        {
            sendDeleteItemRPC(owner, inv[i].index, qty);
            if (qty < inv[i].amount)
            {
                inv[i].amount -= qty;
                return;
            }
            else if (qty == inv[i].amount)
            {
                inv.removeAt(i);
                return;
            }
            else
            {
                qty -= inv[i].amount;
                inv.removeAt(i);
            }
        }
    }
}

bool Pony::hasInventoryItem(quint32 id, quint32 qty)
{
    for (const InventoryItem& item : inv)
    {
        if (item.id == id)
        {
            if (item.amount >= qty) return true;
            else qty -= item.amount;
        }
    }
    return qty == 0;
}

void Pony::unwearItemAt(quint8 index)
{
    /*bool found=false;
    for (int i=0; i<worn.size();i++)
    {
        if (worn[i].index == index+1)
        {
            found=true;
            int itemSlots = win.wearablePositionsMap[worn[i].id];
            wornSlots = (wornSlots | itemSlots) ^ itemSlots;
            addInventoryItem(worn[i].id, 1);
            worn.removeAt(i);
            break;
        }
    }
    if (!found)
    {
        //win.logMessage("[SEVERE] Couldn't unwear item, index "+QString().setNum(index)+" not found");
        win.logMsg(QObject::tr("%1 UDP: Couldn't unwear item, index %2 not found").arg(LOG_SEVERE).arg(QString().setNum(index)));
        return;
    }
    sendUnwearItemRPC(owner, index);

    Scene* scene = findScene(sceneName);
    if (scene->name.isEmpty())
        win.logMsg(QObject::tr("%1 UDP: Couldn't find the scene for unwearItemRPC, aborting!").arg(LOG_SEVERE));
    else
    {
        for (Player* dest : scene->players)
            if (dest->pony.netviewId != netviewId)
                sendUnwearItemRPC(this, dest, index);
    }*/
}

bool Pony::tryWearItem(quint8 invSlot)
{
    /*//win.logMessage("Invslot is "+QString().setNum(invSlot));
    uint32_t id = -1;
    uint32_t itemSlots;
    for (int i=0; i<inv.size(); i++)
    {
        if (inv[i].index == invSlot)
        {
            id = inv[i].id;

            itemSlots = loe.wearablePositionsMap[id];

            if (wornSlots & itemSlots)
            {
                win.logMsg(QObject::tr("%1 UDP: Can't wear item: slots occupied").arg(LOG_INFO));
                return false;
            }

            sendDeleteItemRPC(owner,inv[i].index,1);
            if (inv[i].amount>1)
                inv[i].amount--;
            else
                inv.removeAt(i);
            break;
        }
    }
    if (id == (uint32_t)-1)
    {
        win.logMsg(QObject::tr("%1 UDP: Index not found").arg(LOG_ERROR));
        return false;
    }
    wornSlots |= itemSlots;

    WearableItem item;
    item.id = id;
    item.index = wearablePositionsToSlot(itemSlots);


    //win.logMessage("Wearing at slot "+QString().setNum(item.index));
    wornItm << item;
    sendWearItemRPC(owner, item);

    Scene* scene = findScene(sceneName);
    if (scene->name.isEmpty())
        win.logMsg(QObject::tr("%1 UDP: Couldn't find the scene for unwearItemRPC, aborting!").arg(LOG_SEVERE));
    else
    {
        for (Player* dest : scene->players)
            if (dest->pony.netviewId != netviewId)
                sendWearItemRPC(this, dest, item);
    }

    return true;*/
}

void Pony::takeDamage(unsigned amount)
{
    if (health <= (float)amount/defense)
        kill();
    else
    {
        health -= (float)amount/defense;
        Scene* scene = findScene(sceneName);
        for (Player* player : scene->players)
        {
            sendSetStatRPC(player, netviewId, 1, health);
        }
    }
}

void Pony::kill()
{
    health = 0;
    dead = true;

    Scene* scene = findScene(sceneName);
    for (Player* player : scene->players)
    {
        if (player->pony.netviewId != netviewId)
            sendNetviewRemove(player, netviewId);
    }

    respawn();
}

void Pony::respawn()
{
    health = maxHealth;

    sendLoadSceneRPC(owner, sceneName);
    dead = false;
}

