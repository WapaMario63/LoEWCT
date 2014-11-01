#include "receiveClientAck.h"
#include "message.h"
#include "player.h"
#include "loewct.h"
#include "mainwindow.h"

void onConnectAckReceived(Player *player)
{
    // Remove the conect SYN|ACK from the send queue
    player->udpSendReliableMutex.lock();
    player->udpSendReliableTimer->stop();
    for (int i=0; i<player->udpSendReliableQueue.size();)
    {
        QByteArray qMsg = player->udpSendReliableQueue[i];
        int pos = 0;
        while (pos < qMsg.size()) // Try to find a SYN|ACK
        {
            quint16 qMsgSize = (((quint16)(quint8)qMsg[pos+3])+(((quint16)(quint8)qMsg[pos+4]) << 8)) / 8+5;
            if ((quint16)(quint8)qMsg[pos] == 0x84) // Remove the msg, now that we're connected
                qMsg = qMsg.left(pos) + qMsg.mid(pos+qMsgSize);
            else pos += qMsgSize;
        }

        if (qMsg.size())
        {
            player->udpSendReliableQueue[i] = qMsg;
            i++;
        }
        else player->udpSendReliableQueue.remove(i);
    }
    if (player->udpSendReliableQueue.size()) player->udpSendReliableTimer->start();
    player->udpSendReliableMutex.unlock();
}

void onAckReceived(QByteArray msg, Player *player)
{
    // Number of messages ACK'd by this message
    int nAcks = ((quint8)msg[3] + (((quint16)(quint8)msg[4])<<8)) / 24;

    if (nAcks)
    {
        // Extract the heads (channel and seq) of the ack'd messages
        QVector<MessageHead> acks;
        for (int i=0; i<nAcks; i++)
        {
            MessageHead head;
            head.channel = (quint8)msg[3*i+5];
            head.seq = ((quint16)(quint8)msg[3*i+6] + (((quint16)(quint8)msg[3*i+7])<<8))*2;

            // If that's not a supported reliable message, there's no point in checking
            if (head.channel >= MsgUserReliableOrdered1 && head.channel <= MsgUserReliableOrdered32)
                acks << head;
        }

        // DEBUG ONLY
        // TODO: Make a LoEWCT PCE command that allows enabling/disabling ACK'd messages logs
        if (acks.size())
        {
            QString ackMsg = QString("[INFO] UDP: Messages acknoledged (");
            for (int i=0; i<acks.size(); i++)
            {
                if (i) ackMsg += "/";
                ackMsg += QString(QByteArray().append(acks[i].channel).toHex())+":"+QString().setNum(acks[i].seq);
            }
            ackMsg += ")";
            win.logMsg(ackMsg);
        }
        // END DEBUG ONLY

        // If there's nothing to check, do nothing
        if (player->udpSendReliableQueue.size() && acks.size())
        {
            //win.logMsg("receiveMessage ACK locking");
            player->udpSendReliableMutex.lock();
            player->udpSendReliableTimer->stop();

            // Remove the ACK'd messages from the reliable send queue
            QByteArray qMsg = player->udpSendReliableQueue[0];
            //win.logMessage("About to remove ACKs from : "+QString(qMsg.toHex()));
            for (int i=0; i<acks.size(); i++)
            {
                int pos=0;
                while (pos < qMsg.size()) // Try to find a msg matching this ACK
                {
                    quint16 seq = ((quint16)(quint8)qMsg[pos+1]) + (((quint16)(quint8)qMsg[pos+2])<<8);
                    quint16 qMsgSize = (((quint16)(quint8)qMsg[pos+3])+(((quint16)(quint8)qMsg[pos+4])<<8))/8+5;
                    if ((quint16)(quint8)qMsg[pos] == acks[i].channel && seq == acks[i].seq) // Remove the msg, now that it was ACK'd
                    {
                        //win.logMsg("Removed message : "+QString().setNum(seq)+" size is "+QString().setNum(qMsgSize));
                        qMsg = qMsg.left(pos) + qMsg.mid(pos+qMsgSize);
                        //win.logMsg("New message is "+QString(qMsg.toHex()));
                    }
                    else pos += qMsgSize;
                }
            }

            // Now update the reliable message queue
            if (qMsg.isEmpty())
            {
                player->udpSendReliableQueue.remove(0); // The whole grouped msg was ACK'd, remove it
                if (player->udpSendReliableQueue.size()) // If there's a next message in the queue, send it
                {
                    win.logMsg(QString("[INFO] UDP: Sending next message in queue"));
                    qMsg = player->udpSendReliableQueue[0];
                    if (loe.udpSocket->writeDatagram(qMsg,QHostAddress(player->IP),player->port) != qMsg.size())
                    {
                        win.logMsg(QString("[INFO] UDP: Error sending last message"));
                        win.logStatusMsg("Restarting UDP server ...");
                        loe.udpSocket->close();

                        if (!loe.udpSocket->bind(Settings::gamePort, QUdpSocket::ReuseAddressHint|QUdpSocket::ShareAddress))
                        {
                            win.logMsg(QString("[SEVERE] UDP: Unable to start server on port ")+QString().setNum(Settings::gamePort));
                            win.logStatusMsg(QString("UDP: Unable to start server on port ")+QString().setNum(Settings::gamePort));
                            loe.stopGameServer();
                            return;
                        }
                    }
                    player->udpSendReliableTimer->start();
                    //win.logMessage("receiveMessage ACK unlocking");
                    player->udpSendReliableMutex.unlock();
                }
                else
                {
                    //win.logMessage("receiveMessage ACK unlocking");
                    player->udpSendReliableMutex.unlock();
                }
            }
        }
    }
}
