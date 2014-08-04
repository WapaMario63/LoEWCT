#ifndef SCENEENTITY_H
#define SCENEENTITY_H

#include <QString>

#include "datatype.h"

// Checks for Entities in a scene.

struct SceneEntity
{
public:
    SceneEntity();

public:
    // Get Entity Info
    QString modelName;
    quint16 id;
    quint16 netviewId;
    // Get Entity Position, Rotation and Scene
    QString sceneName;
    UVector pos;
    UQuaternion rot;
};

#endif // SCENEENTITY_H
