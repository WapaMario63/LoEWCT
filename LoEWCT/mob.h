#ifndef MOB_H
#define MOB_H

#include <QString>

#include "sceneEntity.h"
#include "statsComponent.h"

// This is the main file for handling mobs.

class Mobzone;

class Mob : public SceneEntity, public StatsComponent
{
public:
    enum mobType : unsigned
    {
        birch_dryad,
        bunny,
        cockatrice,
        dragon,
        hornet,
        husky_diamond_dog,
        lantern_monster,
        timberwolf
    };
public:
    explicit Mob(Mobzone* zone);
    void setType(QString ModelName); // Don't change the SceneEntity model named directly

    // statsComponent.h overrides
    virtual void kill() override;
    virtual void respawn() override;
    virtual void takeDamage(unsigned amount) override;

private:
    static UVector getRandomPos(Mobzone* zone); // Returns a random position in this zone

public:
    mobType type;

private:
    Mobzone* spawnZone;
    Mobzone* currentZone;
};

#endif // MOB_H
