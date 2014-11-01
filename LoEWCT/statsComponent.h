#ifndef STATSCOMPONENT_H
#define STATSCOMPONENT_H

struct StatsComponent
{
public:
    virtual void kill()=0; // Kills the entity. Will shedule a respawn
    virtual void respawn()=0; // resets and respawns the entity
    virtual void takeDamage(unsigned amount)=0; // Removes health, update the client, may kill the entity

public:
    float health;
};

#endif // STATSCOMPONENT_H
