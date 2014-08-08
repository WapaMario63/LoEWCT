#ifndef PLAYER_H
#define PLAYER_H

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
    bool dead; // If true, the pony is i nthe room, but not instantiated.
    float maxHealth;
    float defense;
};

// THE MAIN PLAYER CLASS THAT DOES EVERYTHING, BOW TO IT, NOW.
class Player : QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Player)

public:
    Player();
    ~Player();

    // Save Player datas
    static void savePonies(Player* player, QList<Pony> ponies);
    static void savePlayerData(Player* player, QList<Pony> ponies);
    static QList<Pony> loadPonies(Player *player);
    static bool savePlayers(QList<Player*>& playersData);
    static QList<Player*> loadPlayers();
    static Player* findPlayer(QList<Player*>& players, QString uname);
    static Player* findPlayer(QList<Player*>& players, QString uIP, quint16 uport);
    static Player* findPlayer(QList<Player*>& players, quint16 netviewId);
    static void removePlayer(QList<Player*>& players, QString uIP, quint16 uport);
    static void disconnectPlayerCleanup(Player* player);

    // Some more extra UDP stuff
public slots:
    void udpResendLast(); // If a reliable message wasn't ACK'd yet, resend it now.
    void udpDelayedSend(); // Enqueue and send the content of the player's grouped message buffer

public:
    void reset(); // Reconstructs an empty Player
    void resetNetwork(); // Resets all the network-related members

public:
    // Player Information
    QString IP;
    quint16 port;
    QString name;
    QString passhash;
    float lastPingTime;
    int lastPingNumber;
    bool isConnected;

    Pony pony;

    // More UDP stuff, holy crap
    quint16 udpSequenceNumbers[33]; // Next sequence number to use when sending a message
    quint16 udpRecvSequenceNumbers[33]; // Last sequence number received
    QByteArray *receivedDatas;
    QVector<MessageHead> udpRecvMissing; // When a message is skipped, mark it as missing and wait for a retransmission
    QVector<QByteArray> udpSendReliableQueue; // Messages that we're sending and that aren't ACKd yet.
    QByteArray udpSendReliableGroupBuffer; // Groups the udp message in this buffer before sending them
    QTimer* udpSendReliableGroupTimer; // Delays the sending until we finished grouping the messages
    QTimer* udpSendReliableTimer; // If we didn't get an ACK before this timeouts, resend the last message
    QMutex udpSendReliableMutex; // Protects the buffer/queue/timers from concurrency hell

    QByteArray lastValidReceivedAnimation;
    quint8 inGame; // 0:Not in game, 1:Loading, 2:Instantiated & waiting savegame, 3:In game and loaded
    quint16 nReceivedDups; // Number of duplicate packets that we didn't miss and had to discard.
    QDateTime chatRollCooldownEnd; // When the cooldown for the roll chat command ends
};

#endif // PLAYER_H
