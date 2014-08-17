#include "pony.h"
#include "player.h"

#include <QFile>
#include <QDir>

#include "loewct.h"
//#include "utils.h"
#include "serialize.h"
#include "message.h"
//#include "sendMessage.h"
//#include "items.h"
//#include "packetloss.h"
#include "settings.h"

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
    : SceneEntity(), StatsComponent(),
      owner(Owner), dead{false},
      maxHealth{100}, defense{2.0}
{
    modelName = "PlayerBase";
    name = "";
    wornSlots = 0;
    health = maxHealth;
}

Pony::type Pony::getType()
{
    // Variable Uint32
    unsigned char num3;
    int num = 0;
    int num2 = 0;
    int i = 0;
    do
    {
        num3 = ponyData[i]; i++;
        num |= (num3 & 0x7f) << num2;
        num2 += 7;
    } while ((num3 & 0x7f) != 0);
    unsigned off = (uint)num + i;
    return (type)(quint8)ponyData[off];
}

void Pony::saveQuest()
{
    win.logMessage(LOG_INFO+QObject::tr("UDP: Saving quests for %1 (%2)").arg(netviewId, owner->name));

    QDir playerPath(QDir::currentPath());
    playerPath.cd("data");
    playerPath.cd("players");
    playerPath.mkdir(owner->name.toLatin1());

    QFile file(QDir::currentPath()+"/data/players/"+owner->name.toLatin1()+"quests.lqd");
    if (!file.open(QIODevice::ReadWrite))
    {
        win.logMessage(QObject::tr("%1 Error saving quests for %2 (%3)").arg(LOG_SEVERE, netviewId, owner->name));
        return;
    }

    QByteArray questData = file.readAll();

    // Try to find an existing entry for this pony, if found delete it, Then go to the end.
    for (int i=0; i<questData.size();)
    {
        // Read the name
        QString entryName = dataToString(questData.mid(i));
        int nameSize = entryName.size() + getVUint32Size(questData.mid(i));

        //win.logMessage("saveQuests : Reading entry "+entryName);

        quint16 entryDataSize = 4 * dataToUint16(questData.mid(i+nameSize));
        if (entryName == this->name) // Delete the entry, we'll reqrite it at the end
        {
            questData.remove(i, nameSize + entryDataSize + 2);
            break;
        }
        else i += nameSize + entryDataSize + 2;
    }

    // Now add our data at the end of the file
    QByteArray newEntry = stringToData(this->name);
    newEntry += (quint8)(quests)
}
