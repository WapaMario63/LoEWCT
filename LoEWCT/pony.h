#ifndef PONY_H
#define PONY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMutex>
#include <QByteArray>
#include <QDateTime>

#include "dataType.h"
//#include "quest.h"
#include "sceneEntity.h"
#include "statsComponent.h"
#include "settings.h"
//#include "player.h"

#define MAX_INVENTORY_SIZE 12
#define MAX_WORN_ITEMS 32
#define PONYDATA_SIZE 50 // Size of the PonyData minus the name (for August build)

// (!) = NOT THREAD SAFE

class Player;

struct Pony : public SceneEntity, public StatsComponent
{
public:
    enum type
    {
        None,
        EarthPony,
        Unicorn,
        Pegasus,
        Moose
    };

public:
    Pony(Player* Owner);
    virtual ~Pony() = default;

    type getType();

    void saveQuests(); // (!)
    void loadQuests();
    void saveInventory();
    bool loadInventory();

    void addInventoryItem(quint32 id, quint32 qty);
    void removeInventoryItem(quint32 id, quint32 qty);
    bool hasInventoryItem(quint32 id, quint32 qty = 1);
    void unwearItemAt(quint8 index);
    bool tryWearItem(quint8 invSlot);

    virtual void takeDamage(unsigned amount) override;
    virtual void kill() override;
    virtual void respawn() override;

public:
    QByteArray ponyData;
    QString name;
    QList<InventoryItem> inv; // Inventory
    QList<WearableItem> wornItm;
    quint32 nBits;
    //QList<Quest> quests;
    quint32 lastQuest;
    quint32 wornSlots;
    Player* owner;

    bool dead;
    float maxHealth;
    float defense;
};

#endif // PONY_H
