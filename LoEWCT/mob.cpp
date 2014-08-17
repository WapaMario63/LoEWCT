#include "mob.h"
#include "mobzone.h"
#include "loewct.h"
#include "statsComponent.h"
#include "message.h"
#include "settings.h"

unsigned defaultMaxHealth[] = {75, 30, 100, 100, 75, 100, 100, 100};
float defaultDefense[] = {1, 1, 1.5, 10, 0.75, 1, 0.85, 1};

Mob::Mob(Mobzone* zone)
{
    spawnZone = currentZone = zone;
    sceneName = zone->sceneName;

    id = loe.getNewId();
    netviewId = loe.getNewNetviewId();

    pos = getRandomPos(zone);
    rot = {0, (float)(rand()%4-2), 0, 1};

    health = 0; // We need to know the type to know the default health
}

// I was left dumb here, I really have no explanation on what the fuck did I just
// re-write when I was doing like v0.5.X.X_WCT something
// Tux3, lay off those math drugs.

UVector Mob::getRandomPos(Mobzone *zone)
{
    UVector pos;

    // (tux3 had a math orgasm here)

    // "Normalize" our coordinates for the random part
    UVector nStart = {std::min(zone->start.x, zone->end.x),
                      std::min(zone->start.y, zone->end.y),
                      std::min(zone->start.z, zone->end.z)};
    UVector nEnd = {std::max(zone->start.x, zone->end.x),
                    std::max(zone->start.y, zone->end.y),
                    std::max(zone->start.z, zone->end.z)};

    // Pcik a random x/z point on the plane
    int xmod =              floor(abs(nEnd.x-nStart.x));
    if (xmod == 0)          pos.x = nStart.x;
    else if (xmod == 0)     pos.x = -(rand()%(xmod))+nStart.x;
    else                    pos.x = (rand()%(xmod))+nStart.x;

    int zmod =              floor(abs(nEnd.z-nStart.z));
    if (zmod == 0)          pos.z = nStart.z;
    else if (zmod < 0)      pos.z = -(rand()%(zmod))+nStart.z;
    else                    pos.z = (rand()%(zmod))+nStart.z;

    // Compute the diagonal's properties
    float diagVectX = zone->end.x - zone->start.x;
    float diagVectZ = zone->end.y - zone->start.z;
    float diagLength = sqrt(diagVectX*diagVectX + diagVectZ*diagVectZ);

    // Coords of the point projected on the diagonal
    float projectedX = (diagVectX*diagVectX*(pos.x - zone->start.x) + diagVectX*diagVectZ*(pos.z - zone->start.z))
                        / (diagVectX*diagVectX + diagVectZ*diagVectZ);
    float projectedZ = (diagVectX*diagVectZ*(pos.x-zone->start.x) + diagVectZ*diagVectZ*(pos.z-zone->start.z))
                        / (diagVectX*diagVectX + diagVectZ*diagVectZ);
    float projectedLength = sqrt(projectedX*projectedX + projectedZ * projectedZ);

    // Deduce the height (y) of the point
    pos.y = zone->start.y + projectedLength/diagLength * (zone->end.y - zone->start.y);

    return pos;
}
// Actually, can I have some of those math drugs?


void Mob::setType(QString ModelName)
{
    ModelName = ModelName.toLower();
    modelName = ModelName;
    if (modelName == "mobs/brich dryad") type = mobType::birch_dryad;
    else if (modelName == "mobs/bunny") type = mobType::bunny;
    else if (modelName == "mobs/cockatrice") type = mobType::cockatrice;
    else if (modelName == "mobs/dragon") type = mobType::dragon;
    else if (modelName == "mobs/hornet") type = mobType::hornet;
    else if (modelName == "mobs/husky diamond dog") type = mobType::husky_diamond_dog;
    else if (modelName == "mobs/lantern monster") type = mobType::lantern_monster;
    else if (modelName == "mobs/timberwolf") type = mobType::timberwolf;
    else throw QString(LOG_INFO+"[MOBSCRIPT] setType error: unknown type "+modelName);

    health = defaultMaxHealth[type];
}

void Mob::takeDamage(unsigned amount)
{
    if (health <= (float)amount / defaultDefense[type]) kill();
    else
    {
        health -= (float)amount / defaultDefense[type];
        Scene* scene = findScene(sceneName);

        for (Player* player : scene->players)
            sendSetStatRPC(player, netviewId, 1, health);
    }
}

void Mob::kill()
{
    currentZone = spawnZone;
    health = 0;

    Scene* scene = findScene(sceneName);
    for (Player* player : scene->players)
    {
        sendSetStatRPC(player, netviewId, 1, 0);
        sendNetviewRemove(player, netviewId, NetviewRemoveReasonKill);
    }

    respawn();
}

void Mob::respawn()
{
    currentZone = spawnZone;
    pos = getRandomPos(spawnZone);
    rot = {0, (float)(rand()%4-2), 0, 1};

    health = defaultMaxHealth[type];

    Scene* scene = findScene(sceneName);
    for (Player* player : scene->players)
        sendNetviewInstantiate(player, modelName, netviewId, id, pos, rot);
}
