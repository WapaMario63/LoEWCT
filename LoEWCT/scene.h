#ifndef SCENE_H
#define SCENE_H

#include <QString>
#include <QList>

#include "datatype.h"
#include "player.h"
#include "pony.h"
#include "sceneEntity.h"

class Vortex
{
public:
    Vortex();

public:
    quint8 id;
    QString destName;
    UVector destPos;
};

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

#endif // SCENE_H
