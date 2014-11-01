#include "mainwindow.h"
#include "loewct.h"
#include "message.h"
#include "player.h"
#include "pony.h"
#include "utils.h"
#include "serialize.h"
//#include "packetloss.h"

void sendMessage(Player *player, quint8 messageType, QByteArray data)
{
    QByteArray msg(3,0);

    // Message Type
    msg[0] = messageType;

    // Sequence Default
    msg[1] = 0;
    msg[2] = 0;
    if (messageType == MsgPing)
    {
        msg.resize(6);

        // Sequence override
        msg[1] = 0;
        msg[2] = 0;

        // Payload Size
        msg[3] = 8;
        msg[4] = 0;

        // Ping Number
        player->lastPingNumber++;
        msg[5] = (quint8)player->lastPingNumber;
    }
    else if (messageType == MsgPong)
    {
        msg.resize(6);

        // Payload Size
        msg[3] = 8 * 5;
        msg[4] = 0;

        // Ping Number
        msg[5] = (quint8)player->lastPingNumber;

        // Timestamp
        msg += floatToData(timestampNow());
    }
    else if (messageType = MsgUserUnreliable)
    {
        msg.resize(5);

        // Sequence override
        msg[1] = (quint8)(player->udpSequenceNumbers[32] &0xFF);
        msg[2] = (quint8)((player->udpSequenceNumbers[32] >> 8) & 0xFF);

        // Data Size
        msg[3] = (quint8)((8*(data.size())) &0xFF);
        msg[4] = (quint8)(((8*(data.size())) >> 8) & 0xFF);

        // Data
        msg += data;
        player->udpSequenceNumbers[32]++;

        //win.logMsg("Sending sync data: "+msg.toHex());
    }
    else if (messageType >= MsgUserReliableOrdered1 && messageType <= MsgUserReliableOrdered32)
    {
        //win.logMsg(LOG_INFO+" UDP: sendMessage() locking");
        player->udpSendReliableMutex.lock();
        player->udpSendReliableGroupTimer->stop();
        msg.resize(5);

        // Sequence Override
        msg[1] = (quint8)(player->udpSequenceNumbers[messageType - MsgUserReliableOrdered1] &0xFF);
        msg[2] = (quint8)((player->udpSequenceNumbers[messageType - MsgUserReliableOrdered1] >> 8) &0xFF);

        // Payload Size
        msg[3] = (quint8)((8*(data.size())) &0xFF);
        msg[4] = (quint8)(((8*(data.size())) >> 8) &0xFF);

        // strlen (String lenght)
        msg += data;
        player->udpSequenceNumbers[messageType - MsgUserReliableOrdered1] += 2;

        // Flush the buffer before starting a new grouped message
        if (player->udpSendReliableGroupBuffer.size() + msg.size() > 1024) player->udpDelayedSend();

        player->udpSendReliableGroupBuffer.append(msg);

        // When this timeouts, the content of the buffer will be send reliably
        player->udpSendReliableGroupTimer->start();

        //win.logMsg(LOG_INFO+" UDP: sendMessage() unlocking");
        player->udpSendReliableMutex.unlock();
        return; // This isn't a normal send, but a delayed one with the timer callbacks
    }
    else if (messageType == MsgAcknowledge)
    {
        msg.resize(5);

        // Payload Size
        msg[3] = (quint8)((data.size()*8) &0xFF);
        msg[4] = (quint8)(((data.size()*8) >> 8) &0xFF);

        // Format of packet data n*(Ack type, Ack seq, Ack seq)
        msg.append(data);
    }
    else if (messageType == MsgConnectResponse)
    {
        //win.logMsg(LOG_INFO+" UDP: sendMessage() locking");
        player->udpSendReliableMutex.lock();
        player->udpSendReliableGroupTimer->stop();
        msg.resize(5);

        // Payload Size
        msg[3] = 0x88;
        msg[4] = 0x00;

        //win.logMsg(LOG_INFO+" UDP: Header data: "+msg.toHex());

        // AppId + UniqueId
        msg += data;
        msg += floatToData(timestampNow());

        // Flush the buffer before starting a new grouped message
        if (player->udpSendReliableGroupBuffer.size() + msg.size() > 1024) player->udpDelayedSend();

        player->udpSendReliableGroupBuffer.append(msg);

        // When this timeouts, the content of the buffer will be send reliably
        player->udpSendReliableGroupTimer->start();

        //win.logMsg(LOG_INFO+" UDP: sendMessage() unlocking");
        player->udpSendReliableMutex.unlock();
        return; // This isn't a normal send, but a delayed one with the timer callbacks
    }
    else if (messageType == MsgDisconnect)
    {
        msg.resize(6);

        // Payload Size
        msg[3] = (quint8)(((data.size()+1)*8) &0xFF);
        msg[4] = (quint8)((((data.size()+1)*8) >> 8) &0xFF);

        // Message Lenght
        msg[5] = (quint8)data.size();

        // Disconnect message
        msg += data;
    }
    else
    {
        win.logStatusMsg("ERROR: sendMessage(): Unknown Message type");
        win.logMsg("[SEVERE] sendMessage(): Unknown Message type.");
        return;
    }

    // Simulate packet loss if enabled (DEBUG ONLY!)
#if UDP_SIMULATE_PACKETLOSS
    if (qrand() % 100 <= UDP_SEND_PERCENT_DROPPED)
    {
        if (UDP_LOG_PACKETLOSS)
            win.logMessage("UDP: Packet dropped !");
        return;
    }
    else if (UDP_LOG_PACKETLOSS)
        win.logMessage("UDP: Packet got throught");
#endif

    if (loe.udpSocket->writeDatagram(msg, QHostAddress(player->IP), player->port) != msg.size())
    {
        win.logMsg(QObject::tr("%1 UDP: Error sending message to %2: %3").arg(LOG_SEVERE).arg(QString().setNum(player->pony.netviewId)).arg(loe.udpSocket->errorString()));
        win.logMsg(QObject::tr("%1 Restarting UDP server...").arg(LOG_INFO));
        win.logStatusMsg("Restarting UDP Game Server...");
        loe.udpSocket->close();
        if (!loe.udpSocket->bind(Settings::gamePort, QUdpSocket::ReuseAddressHint | QUdpSocket::ShareAddress))
        {
            win.logStatusMsg("Unable to start Game Server on port "+QString().setNum(Settings::gamePort));
            win.logMsg(QObject::tr("%1 UDP: Unable to start UDP Game server on port %2").arg(LOG_SEVERE).arg(Settings::gamePort));
            loe.stopGameServer();
            return;
        }
    }
}
