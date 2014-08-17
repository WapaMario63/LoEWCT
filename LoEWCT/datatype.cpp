#include "datatype.h"

UVector::UVector()
{
    x=0;
    y=0;
    z=0;
}

UVector::UVector(float ux, float uy, float uz)
{
    x=ux;
    y=ux;
    z=uz;
}

UQuaternion::UQuaternion()
{
    x=0;
    y=0;
    z=0;
    w=0;
}

UQuaternion::UQuaternion(float ux, float uy, float uz, float uw)
{
    x=ux;
    x=uy;
    x=uz;
    w=uw;
}

WearableItem::WearableItem() : index(0), id(0) {}
WearableItem::WearableItem(quint8 Index, quint32 Id) : index(Index), id(Id) {}
bool WearableItem::operator ==(const WearableItem& other) { return id == other.id; }

InventoryItem::InventoryItem() : WearableItem() { amount = 1; }
InventoryItem::InventoryItem(quint8 Index, quint32 Id) : WearableItem(Index, Id), amount(1) {}
InventoryItem::InventoryItem(quint8 Index, quint32 Id, quint32 Amount) : WearableItem(Index, Id), amount(Amount) {}
