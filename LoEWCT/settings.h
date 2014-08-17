#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

// Global Settings, these are the things you configure for the server.

// Choose which build you want to compile for.
/// BABSCON = For the January 24-26th Ohaycon and April 18-20th BABScon builds.
/// BRONYCON = For the August 8-10th Build
#define BABSCON_BUILD false
#define BRONYCON_BUILD true

// Default sync interval, you may change if needed.
#define DEFAULT_SYNC_INTERVAL 250

// Server Version String
#define LOEWCT_VERSION "v1.0"

// Server Console Log type
#define LOG_INFO "[INFO] "
#define LOG_SEVERE "[SEVERE] "
#define LOG_ERROR "[ERROR] "
#define LOG_CHAT "[CHAT] " // Only moderation related logs that are done in the in-game chat
#define LOG_QUEST "[QUESTSCRIPT] " // for QuestScript related things only
#define LOG_MOBS "[MOBSCRIPT] " // For mobscript related things only

// Main Config
namespace Settings
{
    extern int loginPort; // Server Port for Log In Server
    extern int gamePort; // Server Port for the game server
    extern QString remoteLoginIP; // IP of the remote login server
    extern int remoteLoginPort; // Port of the remote login server
    extern int remoteLoginTimeout; // Time before giving up connecting to the remote login server
    extern bool useRemoteLogin; // If we want to use the remote login server or not
    extern int maxRegisteredPlayers; // Maximum number of registered players in the database, can den registration
    extern int pingTimeout; // Maximum time between reception of pings, can disconnect player.
    extern int pingCheckInterval; // Time between ping timeout checks
    extern bool logInfo; // Disables/Enables logMessage, but doesn't affect logStatusMessage (Who is going to use this anyway?)
    extern QString saltPassword; // Used to check passwords between login and game servers, must be the same on al lthe servers involved.
    extern bool enableSessKeyValidation; // Enable Session Key Validation
    extern bool enableLoginServer; // Starts the logIn server.
    extern bool enablePlayeSync; // Sync players' positions.
    extern bool enableGETLog; // Enabe [GET] /log requests
    extern bool enableGameServer; // Starts the Game Server
    extern int maxPlayersConnected; // Maximum number of players connected at the same time, can deny login

    extern QString motdMsg;
    extern QString rulesMsg;
    extern QString helpMessage;
    extern QString serverPrefix;
    extern bool mapTpEnable; // Will be gone once moderation system is implemented
    extern int rollCoolDown;
    extern bool pvp; // Enables Player Vs. Player Combat
}

namespace PlayerSettings
{
    extern bool isMod;
    extern QString banReason;
}

#endif // SETTINGS_H
