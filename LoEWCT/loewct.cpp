#include "loewct.h"

LoEWCT::LoEWCT() :
    cmdPlayer(new Player()),
    usedIds(new bool[65536])
{
    tcpServer = new QTcpServer(this);
    udpSocket = new QUdpSocket(this);
    tcpReceivedDatas = new QByteArray();

    pingTimer = new QTimer(this);

    qsrand(QDateTime::currentMSecsSinceEpoch());
    srand(QDateTime::currentMSecsSinceEpoch());
}

int LoEWCT::getNewNetviewId()
{
    int i;

    for (i=0; i<65536; i++) usedIds[i] = false;
    for (int c=0; c<udpPlayers.size(); c++) usedIds[udpPlayers[c]->pony.netviewId] = true;

    i = 0;
    while (usedIds[i]) i++;

    return i;
}

int LoEWCT::getNewId()
{
    int i;

    for (i=0; i<65536; i++) usedIds[i] = false;
    for (int c=0; c<npcs.size(); c++) usedIds[npcs[c]->id] = true;
    for (int c=0; c<udpPlayers.size(); c++) usedIds[udpPlayers[c]->pony.id] = true;

    i = 0;
    while (usedIds[i]) i++;

    return i;
}

