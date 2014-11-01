#ifndef UDP_H
#define UDP_H

class QUdpSocket;

void udpProcessPendingDatagrams();
void restartUdpServer();

extern QUdpSocket* udpSocket;

#endif // UDP_H
