#ifndef MESSAGE_H
#define MESSAGE_H

// This file is liek the most complicated one.
// Ehem, this file acesses a lot of the game's functions so the server can use them.

// Hacky at best indeed.

// This one... something related to player's stats/state
enum NetviewRemoveReasonCodes
{
    NetviewRemoveReasonDefault = 0,
    NetviewRemoveReasonKill = 1
};

// All of the game's message types.
enum MessageTypes
{
    MsgUnconnected = 0
};

#endif // MESSAGE_H
