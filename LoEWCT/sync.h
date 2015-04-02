#ifndef SYNC_H
#define SYNC_H

#include <QObject>
#include <QTimer>
#include "player.h"
#include "pony.h"

#define XMIN -2500
#define YMIN -1000
#define ZMIN -2500

#define XMAX 2500
#define YMAX 2500
#define ZMAX 2500

#define ROTMIN -6.283185
#define ROTMAX 6.283185

#define PosRSSize 16
#define RotRSSize 8

#define DEFAULT_SYNC_INTERVAL 250

class Sync : public QObject
{
    Q_OBJECT
public:
    explicit Sync(QObject* parent = 0);
    void startSync();
    void stopSync();

    void sendSyncMessage(Player *source, Player *dest);

    static void receiveSyncMessage(Player* player, QByteArray data);

public slots:
    void doSync();

private:
    QTimer* syncTimer;
};

#endif // SYNC_H
