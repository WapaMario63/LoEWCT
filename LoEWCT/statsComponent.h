#ifndef STATSCOMPONENT_H
#define STATSCOMPONENT_H

// Stores a global function for simple actions and stats from ponies/players

// Can be overriden anytime.

struct StatsComponent
{
public:
    virtual void kill()=0; // Kills an entity. Will Shedule Respawn.
    virtual void respawn()=0; // Resets and respawns the entity
    virtual void takeDamage(unsigned amount)=0; // Removes health (AKA health depleats), update client, may kill the entity
public:
    float health;

    // Coming Soon
    //float energy;
};

// Mob Stats

/**
  This part contains default stats for the Mobs
  Arrays are indexed by the enum MobType
**/

#include "mob.h"

extern unsigned defaultMaxHealth[];
extern float defaultDefense[];

#endif // STATSCOMPONENT_H
