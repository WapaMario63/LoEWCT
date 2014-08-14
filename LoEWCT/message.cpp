#include "message.h"

#include "player.h"
#include "loewct.h"
#include "serialize.h"
//#include "mob.h"
//#include "mobsparser.h"
//#include "mobstats.h"
//#include "animation.h"
//#include "settings.h"

// File-Global game-entering mutex (to prevent multiple instantiates/clones)
static QMutex levelLoadMutex;

void sendPonies(Player *player)
{
    // The full request is like a normal sendPonies but with all the serialized ponies at the end
    QList<Pony> ponies = Player::loadPonies(player);
    quint32 ponyDataSize = 0;

    for (int i=0; i<ponies.size(); i++) poniesDataSize += ponies[i].ponyData.size();

    QByteArray data(5, 0);
    data[0] = 1; // Request Number from client

    // Number of Ponies
    data[1] = (quint8)(ponies.size()&0xFF);
    data[2] = (quint8)((ponies.size()>>8)&0xFF);
    data[3] = (quint8)((ponies.size()>>16)&0xFF);
    data[4] = (quint8)((ponies.size()>>24)&0xFF);

    for (int i=0; i<ponies.size(); i++) data += ponies[i].ponyData;

    win.logMessage();
}
