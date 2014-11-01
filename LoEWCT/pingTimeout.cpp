#include "loewct.h"
#include "mainwindow.h"
#include "utils.h"
#include "message.h"

void LoEWCT::checkPingTimeouts()
{
    //win.logMsg("CHECKING PING TIMEOUT");
    for (int i=0; i<udpPlayers.size(); i++)
    {
        //if (!udpPlayers[i].connected || !udpPlayers[i].port)
        //    continue;

        // Check pint Timeout
        int time (timestampNow() - udpPlayers[i]->lastPingTime);
        //win.logMsg(QString().setNum(time)+"s");
        if (time > Settings::pingTimeout)
        {
            win.logMsg(QObject::tr("%1 UDP: Ping timeout: (%2s) for %3 (player %4)").arg(LOG_INFO).arg(QString().setNum((int)timestampNow() - udpPlayers[i]->lastPingTime)).arg(QString().setNum(udpPlayers[i]->pony.netviewId)).arg(udpPlayers[i]->name));
            udpPlayers[i]->isConnected = false;
            sendMessage(udpPlayers[i], MsgDisconnect, "Connection Timed Out \n(Ping Time Out)");
            Player::disconnectPlayerCleanUp(udpPlayers[i]);
        }

        // Send a ping to prevent the client timing out on us

        // Comment this if "[INFO] Pong Received" is being spammed in the console.
        sendMessage(udpPlayers[i], MsgPing);
    }
}
