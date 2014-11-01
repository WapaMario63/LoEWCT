#ifndef RECEIVECLIENTACK_H
#define RECEIVECLIENTACK_H

/*
 * This unit contains handlers to clean up the reliable message sending queue
 * Acknowledged messages are removed from queue
 */

#include <QByteArray>

class Player;

void onConnectAckReceived(Player* player);
void onAckReceived(QByteArray msg, Player* player);

#endif // RECEIVECLIENTACK_H
