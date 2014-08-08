#ifndef MAPS_H
#define MAPS_H

#include <QString>
#include <QList>

#include "datatype.h"
#include "player.h"
#include "sceneEntity.h"

// This file handles everything about the game's maps (known here as scene)

// You know those things that when you touch them it teleports you to another location?
// This class handles those, they are called vortexes, for some, reason.

class Vortex
{
public:
    Vortex();

public:
    quint8 id;
    QString destName;
    UVector destPos;
};

// Main class for handling maps.

class Scene
{
public:
    Scene(QString sceneName);

public:
    QString name;
    QList<Vortex> vortexes;
    QList<Player*> players; // Used by the 01 sync function
};

Scene* findScene(QString sceneName);
Vortex findVortex(QString sceneName, quint8 id);
Vortex findVortex(Scene* scene, quint8 id);

#endif // MAPS_H
