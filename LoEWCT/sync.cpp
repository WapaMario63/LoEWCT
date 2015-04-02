#include "sync.h"
#include "loewct.h"
#include "message.h"
#include "utils.h"
#include "serialize.h"

Sync::Sync(QObject *parent)
    : QObject(parent)
{
    syncTimer = new QTimer(this);
    connect(syncTimer, SIGNAL(timeout()), this, SLOT(doSync()));
}

void Sync::startSync() { syncTimer->start(loe.syncInterval); }
void Sync::stopSync() { syncTimer->stop(); }

void Sync::sendSyncMessage(Player *source, Player *dest)
{
    QByteArray data(2,0);
    data[0] = (quint8)(source->pony.netviewId&0xFF);
    data[1] = (quint8)((source->pony.netviewId>>8)&0xFF);

    data += floatToData(timestampNow());

    data += floatToData(source->pony.pos.x);
    data += floatToData(source->pony.pos.y);
    data += floatToData(source->pony.pos.z);

    data += rangedSingleToData(source->pony.rot.y, ROTMIN, ROTMAX, RotRSSize);

    sendMessage(dest, MsgUserUnreliable, data);
}

// mlkj's old TODO.
// TODO: Test ranged singles on PonyVille with the bounds from the text assets
// Or maybe test the command that gives the bounds to the clients
void Sync::receiveSyncMessage(Player *player, QByteArray data) // Receives the =1 updates from each player
{
    if (player->inGame < 2) return; // A Sync message while loading would teleport use to a wrong position

    // 5 and 6 are id and id >> 8
    player->pony.pos.x = dataToFloat(data.mid(11));
    player->pony.pos.y = dataToFloat(data.mid(15));
    player->pony.pos.z = dataToFloat(data.mid(19));

    if (data.size() >= 23) player->pony.rot.y = dataToRangedSingle(ROTMIN, ROTMAX, RotRSSize, data.mid(23,1));
    if (data.size() >= 25)
    {
        player->pony.rot.x = dataToRangedSingle(ROTMIN, ROTMAX, RotRSSize, data.mid(24,1));
        player->pony.rot.z = dataToRangedSingle(ROTMIN, ROTMAX, RotRSSize, data.mid(25,1));
    }
}

void Sync::doSync()
{
    for (int i=0; i<loe.scenes.size(); i++)
    {
        if (loe.scenes[i].players.size() < 2) continue;
        for (int j=0; j<loe.scenes[i].players.size(); j++)
        {
            for (int k=0; k<loe.scenes[i].players.size(); k++)
            {
                if (j == k) continue;
                sendSyncMessage(loe.scenes[i].players[j], loe.scenes[i].players[k]);
            }
        }
    }
}
