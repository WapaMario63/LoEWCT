#ifndef PONY_H
#define PONY_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QTimer>
#include <QMutex>
#include <QByteArray>
#include <QDateTime>

#include "datatype.h"
#include "sceneEntity.h"
#include "statsComponent.h"
#include "player.h"

// Define Maximun Inventory size and maximun worn items.
#define MAX_INVENTORY_SIZE 12
#define MAX_WORN_ITEMS 32

/*
 * LEGEND:
 * (!) = NOT THREAD SAFE!
 */

// Main Pony Class (even though it's just a structure), inherits the god (AKA Player class)
struct Pony : public SceneEntity, public StatsComponent
{
public:
    // Set Pony types
    enum type
    {
        None,
        EarthPony,
        Unicorn,
        Pegasus,
        Moose // IT IS IN THE GAME GUYS
    };

public:
    Pony(Player* Owner);
    virtual ~Pony()=default;

    // Get Pony type
    type getType();

    // Save and Load player's pony's data
    void saveQuest(); // Saves the state of all quests (!)
    void loadQuest(); // Loads the state of all the quests
    void saveInventory(); // Saves worn/possesed items and bits. (!)
    void loadInventory(); // Loads worn/possesed items and bits. False on error.
    void addInventoryItem(quint32 id, quint32 qty);
    void removeInventoryItem(quint32 id, quint32 qty); ///< Removes qty of the item from the inventory
    bool hasInventoryItem(quint32 id, quint32 qty=1); ///< Whether of not there are qty of this item in inventory
    void unwearItemAt(quint8 index); ///< Unwear the item at the position index
    bool tryWearItem(quint8 invSlot); ///< Tries to wear this item. Must be in the inventory

    // Overrides statsComponent.h's function
    virtual void takeDamage(unsigned amount) override; ///< Remove health, update the client, may kill the pony
    virtual void kill() override; ///< Kills the player. He'll respawn.
    virtual void respawn() override; ///< Respawn the player at the default spawn of his scene

public:
    QByteArray ponyData; // Pony's ponyCode converted to base64
    QString name; // Pony's Name
    QList<InventoryItem> inv; // Pony's Inventory
    QList<WearableItem> worn; // Pony's Worn items
    quint32 nBits; // Number of Bits (currency)
    //QList<Quest> quests; // State of the pony's quests
    quint32 lastQuest; // Last QuestScript+ the player ran.
    quint32 wornSlots; // Flag of the used item-wearing slots (See enum WearablePositions at dataType.h)
    Player* owner;
    bool dead; // If true, the pony is in the room, but not instantiated.
    float maxHealth;
    float defense;
};

#endif // PONY_H
