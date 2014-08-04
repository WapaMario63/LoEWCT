#ifndef DATATYPE_H
#define DATATYPE_H

#include <qglobal.h>

// This is just some data types so we can access some of LoE's stuff
// Well actually just math stuff... Actually I have no idea ask tux3.

// LoE Cordinates?
class UVector
{
public:
    UVector();
    UVector(float ux, float uy, float uz);

public:
    float x;
    float y;
    float z;
};

typedef struct UVector UVector;

// LoE Roatation Cordinates?
class UQuaternion
{
public:
    UQuaternion();
    UQuaternion(float ux, float uy, float uz, float, uw);

public:
    float x;
    float y;
    float z;
    float w;
};
typedef struct UQuaternion UQuaternion;

// LoE Item Wearable data handling... stuff.
class WearableItem
{
public:
    WearableItem();
    WearableItem(quint8 Index, quint32 Id);
    bool operator==(const WearableItem& other);
public:
    quint8 index;
    quint32 id;
};

// Class name says it all and enum list says it all.
enum class WearablePositions : uint32_t
{
    None = 0,
    Tail = 0x1,
    Pants = 0x2,
    FrontSocks = 0x4,
    BackSocks = 0x8,
    FrontShoes = 0x10,
    BackShoes = 0x20,
    Saddle = 0x80,
    Shirt = 0x80,
    Necklace = 0x100,
    Mouth = 0x200, // Wat, are there going to be braces or something in the game one day or...?
    Mask = 0x400,
    Eyes = 0x800,
    Ears = 0x1000,
    FrontKnees = 0x2000,
    BackKnees = 0x4000,
    SaddleBags = 0x40000000,
    Hat = 0x80000000
};

// LoE Inventory data... stuff.
class InventoryItem : public WearableItem
{
public:
    InventoryItem();
    InventoryItem(quint8 Index, quint32 Id);
    InventoryItem(quint8 Index, quint32 Id, quint32 Amount);
public:
    quint32 amount;
};

// I have no idea what is this.
struct MessageHead
{
    quint16 channel;
    quint16 seq;

    bool operator ==(const MessageHead& other) const
    {
        return (channel==other.channel && seq==other.seq);
    }
};

#endif // DATATYPE_H
