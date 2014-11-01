#include "loewct.h"

LoEWCT::LoEWCT() :
    usedids(new bool[65536])
{
    tcpServer = new QTcpServer(this);
    udpSocket = new QUdpSocket(this);
    tcpReceivedDatas = new QByteArray();

    pingTimer = new QTimer(this);

    qsrand(QDateTime::currentMSecsSinceEpoch());
    srand(QDateTime::currentMSecsSinceEpoch());
}

LoEWCT::~LoEWCT()
{
    Settings::logInfos = false;
}

// Threading, Game Server gets its own thread, Log In Server gets another, and the UI itself gets another.
// >inb4
//  >manual memory management
//  Kill yourself.
void LoEWCTThread::run()
{
    if (useGameServer && Settings::enableGameServer)
    {

    }

    if (useLoginServer && Settings::enableLoginServer)
    {

    }
}

void LoEWCT::startGameServer()
{

}

void LoEWCT::stopGameServer()
{

}

void LoEWCT::startLoginServer()
{

}

void LoEWCT::stopLoginServer()
{

}

int LoEWCT::getNewNetviewId()
{
    int i;

    for (i=0; i<65536; i++) usedids[i] = false;
    for (int c=0; c<npcs.size(); c++) usedids[npcs[c]->netviewId] = true;
    for (int c=0; c<udpPlayers.size(); c++) usedids[udpPlayers[c]->pony.netviewId] = true;

    i = 0;
    while (usedids[i]) i++;

    return i;
}

int LoEWCT::getNewId()
{
    int i;

    for (i=0; i<65536; i++) usedids[i] = false;
    for (int c=0; c<npcs.size(); c++) usedids[npcs[c]->id] = true;
    for (int c=0; c<udpPlayers.size(); c++) usedids[udpPlayers[c]->pony.id] = true;

    i = 0;
    while (usedids[i]) i++;

    return i;
}

