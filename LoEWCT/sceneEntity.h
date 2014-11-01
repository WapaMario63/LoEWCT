#ifndef SCENEENTITY_H
#define SCENEENTITY_H

#include <QString>

#include "datatype.h"

struct SceneEntity
{
public:
    SceneEntity();

public:
    // Infos
    QString modelName;
    quint16 id;
    quint16 netviewId;

    // Pos
    QString sceneName;
    UVector pos;
    UQuaternion rot;
};

#endif // SCENEENTITY_H
