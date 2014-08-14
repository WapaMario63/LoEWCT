#include "loewct.h"

LoEWCT::LoEWCT() :
    cmdPlayer(new Player()),
    usedIds(new bool[65536])
{
    tcpServer = new QTcpServer(this);
    udpSocket = new QUdpSocket(this);
}
