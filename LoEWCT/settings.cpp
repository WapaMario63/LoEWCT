#include "settings.h"

// Normal Config

int Settings::loginPort; // Port for the login server
int Settings::gamePort; // Port for the game server
QString Settings::remoteLoginIP; // IP of the remote login server
int Settings::remoteLoginPort; // Port of the remote login server
int Settings::remoteLoginTimeout; // Time before we give up connecting to the remote login server
bool Settings::useRemoteLogin; // Whever or not to use the remote login server
int Settings::maxRegistered; // Max number of registered players in database, can deny registration
int Settings::pingTimeout; // Max time between recdption of pings, can disconnect player
int Settings::pingCheckInterval; // Time between ping timeout checks
bool Settings::logInfos; // Can disable logMessage, but doesn't affect logStatusMessage
QString Settings::saltPassword; // Used to check passwords between login and game servers, must be the same on all the servers involved
bool Settings::enableSessKeyValidation; // Enable Session Key Validation
bool Settings::enableLoginServer; // Starts a login server
bool Settings::enableMultiplayer; // Sync players' positions
bool Settings::enableGetlog; // Enable GET /log requests
bool Settings::enableGameServer; // Starts a game server
int Settings::maxConnected; // Max numbre of players connected at the same time, can deny login

// LoEWCT Config
QString Settings::helpMessage;
QString Settings::motdMessage;
QString Settings::rulesMessage;
QString Settings::serverPrefix;
bool Settings::pvp;
bool Settings::playerJoingMsg;
bool Settings::mapTpEnable;
int Settings::rollCoolDown;
quint16 Settings::maxPacketDups;
bool Settings::lmmPlayer;
bool Settings::useReliableAnimation = true;
int Settings::anheroTime;
