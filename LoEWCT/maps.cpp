#include "maps.h"
#include "loewct.h"

Vortex::Vortex()
{
    id = 0;
    destName = QString();
    destPos = UVector();
}

Scene::Scene (QString sceneName)
{
    name = sceneName.toLower();
    vortexes = QList<Vortex>();
}

Scene* findScene(QString sceneName)
{
    for (int i=0; i<loe.scenes.size(); i++)
        if (loe.scenes[i].name.toLower() == sceneName.toLower())
            return &loe.scenes[i];
    return new Scene("");
}

Vortex findVortex(QString sceneName, quint8 id)
{
    Scene scene(sceneName);
    for (int i=0; i<loe.scenes.size(); i++)
        if (loe.scenes[i].name.toLower() == sceneName.toLower())
            scene = loe.scenes[i];

    for (int i=0; i<scene.vortexes.size(); i++)
        if (scene.vortexes[i].id == id)
            return scene.vortexes[i];

    return Vortex();
}

Vortex findVortex(Scene *scene, quint8 id)
{
    for (int i=0; i<scene->vortexes.size(); i++)
        if (scene->vortexes[i].id == id)
            return scene->vortexes[i];

    return Vortex();
}
