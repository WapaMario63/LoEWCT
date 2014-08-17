#ifndef MOBZONE_H
#define MOBZONE_H

#include <QMap>
#include <QPair>

#include "datatype.h"

struct Mobzone
{
    UVector start, end; // Bounds of the mobzone

    QString sceneName;

    // Map of adjacent of mobzones and the intersection line
    QMap<Mobzone, QPair<UVector, UVector>> adjacents;
};

#endif // MOBZONE_H
