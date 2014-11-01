#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

// Log Prefixes
#define LOG_INFO "[INFO]"
#define LOG_ERROR "[ERROR]"
#define LOG_SEVERE "[SEVERE]"

#define LOG_PLUGIN "[PLUGIN]"

// Default settings
#define DEFAULT_MAX_CONNECTED 256
#define DEFAULT_LOG_INFOSMESSAGES true
#define DEFAULT_SALT_PASSWORD "Change Me"

#define DEFAULT_ENABLE_LOGIN_SERVER true
#define DEFAULT_LOGIN_PORT 1034
#define DEFAULT_MAX_REGISTERED 4096
#define DEFAULT_USE_REMOTE_LOGIN false
#define DEFAULT_REMOTE_LOGIN_IP "127.0.0.1"
#define DEFAULT_REMOTE_LOGIN_PORT 1034
#define DEFAULT_REMOTE_LOGIN_TIMEOUT 5000
#define DEFAULT_ENABLE_GETLOG true
#define DEFAULT_SESSKEY_VALIDATION true

#define DEFAULT_ENABLE_GAME_SERVER true
#define DEFAULT_GAME_PORT 1039
#define DEFAULT_ENABLE_MULTIPLAYER true
#define DEFAULT_SYNC_INTERVAL 200
#define DEFAULT_PING_TIMEOUT 25
#define DEFAULT_PING_CHECK 3000
#define DEFAULT_PVP false

#define MAX_PACKET_DUPS 1000

// Use either BABSCon/Ohaycon clients or BronyCon (August 8-10) Client
#define USE_BABSCON_CLIENT true
#define USE_BRONYCON_CLIENT false



namespace Settings
{
    // Server Settings
    extern int loginPort; // Port for the login server
    extern int gamePort; // Port for the game server
    extern QString remoteLoginIP; // IP of the remote login server
    extern int remoteLoginPort; // Port of the remote login server
    extern int remoteLoginTimeout; // Time before we give up connecting to the remote login server
    extern bool useRemoteLogin; // Whether or not to use the remote login server
    extern int maxConnected; // Max number of players connected at the same time, can deny login
    extern int maxRegistered; // Max number of registered players in database, can deny registration
    extern int pingTimeout; // Max time between recdption of pings, can disconnect player
    extern int pingCheckInterval; // Time between ping timeout checks
    extern bool logInfos; // Can disable logMessage, but doesn't affect logStatusMessage
    extern QString saltPassword; // Used to check passwords between login and game servers, must be the same on all the servers involved
    extern bool enableSessKeyValidation; // Enable Session Key Validation
    extern bool enableLoginServer; // Starts a login server
    extern bool enableGameServer; // Starts a game server
    extern bool enableMultiplayer; // Sync players' positions
    extern bool enableGetlog; // Enable GET /log requests

    // [LoEWCT] Settings
    extern bool pvp; // Enables player versus player fights

    extern bool mapTpEnable;
    extern bool playerJoingMsg;
    extern int rollCoolDown;
    extern QString motdMessage;
    extern QString rulesMessage;
    extern QString serverPrefix;
    extern QString helpMessage;
    extern quint16 maxPacketDups;
    extern bool lmmPlayer;
    extern int anheroTime;
    extern bool useReliableAnimation;

}

namespace PlayerData
{

    extern bool isModerator;
    extern QString banReason;

}

#endif // SETTINGS_H
