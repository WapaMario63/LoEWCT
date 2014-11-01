#include <QUdpSocket>
#include <QCryptographicHash>

#include "mainwindow.h"
#include "loewct.h"
#include "udp.h"
#include "settings.h"
#include "message.h"
#include "serialize.h"
#include "player.h"
#include "pony.h"

using namespace Settings;

QUdpSocket* udpSocket;

void restartUdpServer()
{
    win.logMsg(QObject::tr("%1 Restarting UDP server").arg(LOG_INFO));
    win.logStatusMsg(QObject::tr("Restarting UDP server..."));

    udpSocket->close();
    if (!udpSocket->bind(gamePort, QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress))
    {
        win.logMsg(QObject::tr("%1 UDP: Unable to start server on port %2").arg(LOG_INFO).arg(gamePort));
        loe.stopGameServer();
        return;
    }
}

void udpProcessPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams())
    {
        QHostAddress rAddr;
        quint16 rPort;
        QByteArray datagram;
        quint64 dataRead = 0;
        int datagramSize = udpSocket->pendingDatagramSize();
        datagram.resize(datagramSize);

        while (dataRead < datagram.size())
        {
            qint64 readNow = udpSocket->readDatagram(datagram.data()+dataRead, datagramSize, &rAddr, &rPort);
            if (readNow != -1)
            {
                dataRead += readNow; // Remember the total number of bytes read, so we know when to stop
                if (datagramSize > (datagram.size() - dataRead)) // Make sure we don't overflow
                    datagramSize = (datagram.size() - dataRead);
            }
            else
            {
                win.logMsg(QObject::tr("%1 UDP Socket error: %2").arg(LOG_SEVERE).arg(udpSocket->errorString()));
                return;
            }
        }

        // Add player on connection
        if ((unsigned char)datagram[0] == MsgConnect && (unsigned char)datagram[1] == 0
                && (unsigned char)datagram[2] == 0 && datagram.size() >= 22)
        {
            QString name = dataToString(datagram.right(datagram.size()-22));
            int nameFullSize = getVUint32Size(datagram.right(datagram.size()-22))+name.size();
            QString sesskey = dataToString(datagram.right(datagram.size()-22-nameFullSize));
            //logMsg(QString("UDP: Connect detected with name : ")+name);
            //logMsg(QString("UDP: Connect detected with sesskey : ")+sesskey);
            //logMsg(QString("UDP: Datagram was : ")+datagram.toHex());


            bool is_sesskey_valid = true;

            if (enableSessKeyValidation)
            {
                is_sesskey_valid = QCryptographicHash::hash(QString(sesskey.right(40) + saltPassword).toLatin1(), QCryptographicHash::Md5).toHex() == sesskey.left(32);
            }

            if (is_sesskey_valid)
            {
                //logMsg("Sesskey token accepted");

                // Create new player if needed, else just update the player
                Player* newPlayer = Player::findPlayer(loe.udpPlayers, rAddr.toString(), rPort);
                if (newPlayer->IP != rAddr.toString())
                {
                    newPlayer->resetNetwork();
                    //newPlayer->connected = true; // Not really connected until we finish the handshake
                    newPlayer->name = name;
                    newPlayer->IP = rAddr.toString();
                    newPlayer->port = rPort;

                    // Check if we have too many players connected
                    int n=0;
                    for (int i=0; i<loe.udpPlayers.size(); i++)
                        if (loe.udpPlayers[i]->isConnected) n++;
                    if (n >= maxConnected)
                        sendMessage(newPlayer, MsgDisconnect, "Kicked by Server \n\nReason \n-------------------------------\nServer is Full. \nTry Again Later.");
                    else // If not add the player
                        loe.udpPlayers << newPlayer;
                }
                else // IP:Port found in player list
                {
                    if (newPlayer->isConnected)
                    {
                        sendMessage(newPlayer, MsgDisconnect, "Kicked by Server \n\nReason \n-------------------------------\nAlready Connected.");
                        return;
                    }

                    // Check if we have too many players connected
                    int n=0;
                    for (int i=0; i<loe.udpPlayers.size(); i++)
                        if (loe.udpPlayers[i]->isConnected) n++;
                    if (n >= maxConnected)
                        sendMessage(newPlayer, MsgDisconnect, "Kicked by Server \n\nReason \n-------------------------------\nServer is Full. \nTry Again Later.");

                    newPlayer->resetNetwork();
                    newPlayer->name = name;
                    newPlayer->IP = rAddr.toString();
                    newPlayer->port = rPort;
                    //newPlayer->connected = true; // We're not really connected until we finish the handshake
                }
            }
            else
            {
                QString badHash = QCryptographicHash::hash((QString(sesskey.right(40))
                                  + saltPassword).toLatin1(), QCryptographicHash::Md5).toHex();

                win.logMsg(QObject::tr("%1 UDP: Session Key Rejected. Got %2 instead of %3, passhash was %4").arg(LOG_INFO).arg(badHash).arg(sesskey.left(32)).arg(sesskey.right(40)));
                Player* newPlayer = new Player;
                newPlayer->IP = rAddr.toString();
                newPlayer->port = rPort;
                sendMessage(newPlayer, MsgDisconnect, "Kicked by Server \n\nReason \n-------------------------------\nWrong Server Password \n\nThis server is protected with a salt password.");
                return;
            }
        }

        Player* player = Player::findPlayer(loe.udpPlayers, rAddr.toString(), rPort);
        if (player->IP == rAddr.toString() && player->port == rPort)
        {
            // Aquire Datas
            player->receivedDatas->append(datagram);

            // Process Data
            receiveMessage(player);
        }
        else
        {
            win.logMsg(QObject::tr("%1 UDP: Request from unknown player rejected: %2:%3").arg(LOG_INFO).arg(rAddr.toString()).arg(QString().setNum(rPort)));
            // Send disconnect message manually
            QString data("Kicked by Server \n\nReason \n-------------------------------\nYou're not connected, please log in first. (AKA the server has no idea who you are");
            QByteArray msg(6,0);
            msg[0] = MsgDisconnect;
            msg[3] = (quint8)(((data.size()+1)*8)&0xFF);
            msg[4] = (quint8)((((data.size()+1)*8)>>8)&0xFF);
            msg[5] = (quint8)data.size();
            msg += data;
            loe.udpSocket->writeDatagram(msg, rAddr, rPort);
        }
    }
}
