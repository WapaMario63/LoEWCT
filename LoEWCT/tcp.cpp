#include "loewct.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "message.h"
#include "utils.h"
#include "settings.h"

#include <QCryptographicHash>

void LoEWCT::tcpConnectClient()
{
    win.logMsg(QObject::tr("%1 TCP: New Client connected").arg(LOG_INFO));

    QTcpSocket *newClient = tcpServer->nextPendingConnection();
    tcpClientsList << QPair<QTcpSocket*,QByteArray*>(newClient,new QByteArray());

    loe.connect(newClient, SIGNAL(readyRead()), this, SLOT(tcpProcessPendingDatagram()));
    loe.connect(newClient, SIGNAL(disconnected()), this, SLOT(tcpDisconnectClient()));
}

void LoEWCT::tcpDisconnectClient()
{
    // find who's disconnecting, if we can't, just give up.
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) return;

    win.logMsg(QObject::tr("%1 TCP: Client disconnected").arg(LOG_INFO));
    win.disconnect(socket);

    for (int i=0; i<tcpClientsList.size(); i++)
    {
        if (tcpClientsList[i].first == socket)
        {
            delete tcpClientsList[i].second;
            tcpClientsList.removeAt(i);
            break;
        }
    }

    socket->deleteLater();
}

void LoEWCT::tcpProcessPendingDatagram()
{
    // Find who's sending
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == nullptr) return;

    QByteArray* recvBuffer = nullptr;
    for (auto pair : tcpClientsList)
    {
        if (pair.first == socket)
        {
            recvBuffer = pair.second;
            break;
        }
    }
    if (recvBuffer == nullptr)
    {
        win.logMsg(QObject::tr("%1 TCP: Error fetching the socket's associated recv Buffer").arg(LOG_INFO));
        return;
    }

    unsigned nTries = 0;

    // Aquire data

    /// Exit if disconnected, too much retries, malformed HTTP request, or after all requests are processed
    while (socket->state() == QAbstractSocket::ConnectedState && nTries < 3)
    {
        recvBuffer->append(socket->readAll());
        nTries++;

        if (!recvBuffer->size())
        {
            win.logMsg(QObject::tr("%1 TCP: Nothing to read").arg(LOG_INFO));
            continue;
        }

        if (!recvBuffer->startsWith("POST") && !recvBuffer->startsWith("GET")) // Not HTTP, clear the buffer
        {
            win.logMsg(QObject::tr("%1 TCP: Received non-HTTP request: %2").arg(LOG_INFO).arg(*recvBuffer->toHex()));

            recvBuffer->clear();
            socket->close();
            return;
        }
        else if (recvBuffer->contains("Content-Lenght:")) // POST or GET request, wait for Content-Lenght header
        {
            QByteArray contentLenght = *recvBuffer;
            contentLenght = contentLenght.right(contentLenght.size() - contentLenght.indexOf("Content-Lenght:") - 15);
            QList<QByteArray> lenghtList = contentLenght.trimmed().split('\n');
            if (lenghtList.size() > 1) // We want a number on this line and a next line to be sure we've got the full number
            {
                bool isNumeric;
                int lenght = lenghtList[0].trimmed().toInt(&isNumeric);
                if (!isNumeric) // We've got something, but it's not a number
                {
                    win.logMsg(QObject::tr("%1 TCP: Error: Content-Lenght must be a decimal number!").arg(LOG_ERROR));
                    recvBuffer->clear();
                    socket->close();
                    return;
                }

                // Detect and send data files if we need to
                QByteArray data = *recvBuffer;

                win.logMsg(QObject::tr("%1 TCP: Got Content-Lenght request: %2"+data).arg(LOG_INFO));

                // Get the payload only (remove headers)
                data = removeHTTPHeader(data, "POST ");
                data = removeHTTPHeader(data, "GET ");
                data = removeHTTPHeader(data, "User-Agent:");
                data = removeHTTPHeader(data, "Host:");
                data = removeHTTPHeader(data, "host:");
                data = removeHTTPHeader(data, "Accept:");
                data = removeHTTPHeader(data, "Content-Length:");
                data = removeHTTPHeader(data, "Content-Type:");
                data = removeHTTPHeader(data, "Server:");
                data = removeHTTPHeader(data, "Date:");
                data = removeHTTPHeader(data, "Transfert-Encoding:");
                data = removeHTTPHeader(data, "Connection:");
                data = removeHTTPHeader(data, "Vary:");
                data = removeHTTPHeader(data, "X-Powered-By:");
                data = removeHTTPHeader(data, "accept-encoding:");
                data = removeHTTPHeader(data, "if-modified-since:");

                if (data.size() >= lenght) // Wait until we have all the data
                {
                    data.truncate(lenght);

                    // Process data, if the buffer is not empty, keep reading
                    tcpProcessData(data, socket);
                    *recvBuffer = recvBuffer->right(recvBuffer->size() - recvBuffer->indexOf(data) - data.size());
                    if (recvBuffer->isEmpty()) return;
                    nTries = 0;
                }
            }
        }
        else if (recvBuffer->contains("\r\n\r\n")) // POST or GET request, without a Content-Lenght header
        {
            QByteArray data = *recvBuffer;
            data = data.left(data.indexOf("\r\n\r\n")+4);
            int dataSize = data.size();

            win.logMsg(QObject::tr("%1 TCP: Got non-Content Lenght request:"+data).arg(LOG_INFO));

            int i1 = 0;
            do
            {
                i1 = data.indexOf("GET");
                if (i1 != -1)
                {
                    int i2 = data.indexOf("HTTP")-1;
                    QString path = data.mid(i1 + 4, i2-i1-4);
                    if (path == "/log") // GET /log
                    {
                        data = removeHTTPHeader(data, "POST ");
                        data = removeHTTPHeader(data, "GET ");
                        data = removeHTTPHeader(data, "if-modified-since:");
                        data = removeHTTPHeader(data, "accept-encoding:");
                        data = removeHTTPHeader(data, "host:");

                        if (!Settings::enableGetlog) continue;
                        QFile head(QString(NETDATAPATH)+"/dataTextHeader.lnd");
                        head.open(QIODevice::ReadOnly);
                        if (!head.isOpen())
                        {
                            win.logMsg(QObject::tr("%1 TCP: Can't open header: %2").arg(LOG_ERROR).arg(head.errorString()));
                            continue;
                        }
                        QByteArray logData = win.ui->consoleLog->toPlainText().toLatin1();
                        socket->write(head.readAll());
                        socket->write(QString("Content-Lenght: "+QString().setNum(logData.size())+"\r\n\r\n").toLocal8Bit());
                        socket->write(logData);
                        head.close();
                        win.logMsg(QObject::tr("%1 TCP: Sent log to %2").arg(LOG_INFO).arg(socket->peerAddress().toString()));
                        continue;
                    }
                    // Other GETs (not getLog)
                    data = removeHTTPHeader(data, "POST ");
                    data = removeHTTPHeader(data, "GET ");
                    win.logMsg(QObject::tr("%1 TCP: Replying to HTTP GET %2").arg(LOG_INFO).arg(path));
                    QFile head(QString(NETDATAPATH)+"/dataHeader.lnd");
                    QFile res("data/"+path);
                    head.open(QIODevice::ReadOnly);
                    if (!head.isOpen())
                    {
                        win.logMsg(QObject::tr("%1 TCP: Can't open header: %2").arg(LOG_SEVERE).arg(head.errorString()));
                        continue;
                    }
                    res.open(QIODevice::ReadOnly);
                    if (!res.isOpen())
                    {
                        win.logMsg(QObject::tr("%1 TCP: File not found. Trying to open 304").arg(LOG_SEVERE));
                        head.close();

                        // If we 404, we send a 304 Not Modified, and the client will use it's local version
                        // The game clients chokes if we send anything but a 200 or 304 back

                        QFile head404(QString(NETDATAPATH)+"/notmodifie.lnd");
                        head404.open(QIODevice::ReadOnly);
                        if (!head404.isOpen())
                        {
                            win.logMsg(QObject::tr("%1 TCP: Can't open 304 Not Modified Header: %2").arg(LOG_SEVERE).arg(head404.errorString()));
                            continue;
                        }
                        socket->write(head404.readAll());
                        head404.close();
                        continue;
                    }
                    socket->write(head.readAll());
                    socket->write(QString("Content-Lenght: "+QString().setNum(res.size())+"\r\n\r\n").toLocal8Bit());
                    socket->write(res.readAll());
                    head.close();
                    res.close();

                    win.logMsg(QObject::tr("%1 TCP: Sent %2 bytes").arg(LOG_INFO).arg(QString().setNum(res.size()+head.size())));
                }
            } while (i1 != -1);

            *recvBuffer = recvBuffer->mid(dataSize);
        }
    }
}

// Remember to fill this when player class is done.
void LoEWCT::tcpProcessData(QByteArray data, QTcpSocket *socket)
{
    QByteArray* recvBuffer = nullptr;
    for (auto pair : tcpClientsList)
    {
        if (pair.first == socket)
        {
            recvBuffer = pair.second;
            break;
        }
    }
    if (recvBuffer == nullptr)
    {
        win.logMsg(QObject::tr("%1 TCP: Error fetching the socket's associated recv buffer").arg(LOG_ERROR));
        return;
    }

    //win.logMsg("[INFO] TCP: tpcProcessData() received: "+data);

    // LogIn request (forwarded)
    if (Settings::useRemoteLogin && recvBuffer->contains("commfunction=login&") && recvBuffer->contains("&version="))
    {
        win.logMsg("[INFO] TCP: Remote Login is not implemented yet.");
        // We need to add the client with his IP/port/passhash to tcpPlayers if he isn't already there
        Player newPlayer;
        newPlayer.IP = socket->peerAddress().toIPv4Address();
        newPlayer.port = socket->peerPort();
        QString passhash = QString(*recvBuffer);
        passhash = passhash.mid(passhash.indexOf("passhash=")+9);
        passhash.truncate(passhash.indexOf('&'));
        newPlayer.passhash = passhash;
        win.logMsg(QObject::tr("%1 TCP: IP: %2, Passhash: %3").arg(LOG_INFO).arg(newPlayer.IP).arg(newPlayer.passhash));

        // Then connect to the remote and forward the client's requests
        if (!remoteLoginSock.isOpen())
        {
            remoteLoginSock.connectToHost(Settings::remoteLoginIP, Settings::remoteLoginPort);
            remoteLoginSock.waitForConnected(Settings::remoteLoginTimeout);
            if (!remoteLoginSock.isOpen())
            {
                win.logMsg(QObject::tr("%1 TCP: Can't connect to the remote login server. (Connection Timed Out)"));
                return;
            }
        }
        // We just blidnly send everything that we're going to remove from recvBuffer at the end of tcpProcessData
        QByteArray toSend = *recvBuffer;
        toSend.left(toSend.indexOf(data) + data.size());
        remoteLoginSock.write(toSend);
    }
    else if (Settings::useRemoteLogin && recvBuffer->contains("Server:")) // Login reply (forwarded)
    {
        win.logMsg("[INFO] TCP: Remote Login is not implemented yet.");
        // First we need to find a player matching the received passhash in tcpPlayers
        // Use the player's IP/port to find a matching socket in tcpClientsList
        // The login headers are all the same, so we can just use loginHeader.bin and send back data
    }
    else if (recvBuffer->contains("commfunction=login&") && recvBuffer->contains("&version=")) // Login request
    {
        QString postData = QString(*recvBuffer);
        *recvBuffer = recvBuffer->right(postData.size() - postData.indexOf("version=") - 8 - 4);

        win.logMsg(QObject::tr("%1 TCP: Login request received."));

        QFile file(QString(NETDATAPATH)+"/loginHeader.lnd");
        QFile fileServersList(SERVERSLISTFILEPATH);
        QFile fileBadPassword(QString(NETDATAPATH)+"/loginWrongPassword.lnd");
        QFile fileAlready(QString(NETDATAPATH)+"/loginAlreadyConnected.lnd");
        QFile fileMaxRegistration(QString(NETDATAPATH)+"/loginMaxRegistered.lnd");
        QFile fileMaxConnected(QString(NETDATAPATH)+"/loginMaxConnected.lnd");

        if (!file.open(QIODevice::ReadOnly) || !fileBadPassword.open(QIODevice::ReadOnly)
            || !fileAlready.open(QIODevice::ReadOnly) || !fileMaxRegistration.open(QIODevice::ReadOnly)
            || !fileMaxConnected.open(QIODevice::ReadOnly) || !fileServersList.open(QIODevice::ReadOnly))
        {
            win.logStatusMsg("SEVERE ERROR: Error reading login network data files (.lnd (LoE Network Data)).");
            win.logMsg(QObject::tr("%1 TCP: Error reading login network data files (.lnd (LoE Network Data)).").arg(LOG_SEVERE));
            loe.stopLoginServer();
        }
        else
        {
            win.logMsg("[INFO] Version: "+postData.mid(postData.indexOf("version=")+8));

            bool ok = true;

            postData = postData.right(postData.size() - postData.indexOf("username=")-9);
            QString username = postData;
            username.truncate(postData.indexOf('&'));
            postData = postData.right(postData.size() - postData.indexOf("passhash=")-9);
            QString passhash = postData;
            passhash.truncate(postData.indexOf('&'));

            win.logMsg("[INFO] IP: "+socket->peerAddress().toString());
            win.logMsg("[INFO] Username: "+username);
            win.logMsg("[INFO] Passhash: "+passhash);

            // Add Player to the players list
            Player* player = Player::findPlayer(tcpPlayers, username);
            if (player->name != username) // Not found, create a new player
            {
                // Check max registered number
                if (tcpPlayers.size() >= Settings::maxRegistered)
                {
                    win.logMsg(QObject::tr("%1 TCP: Registration failed, too many players resgistered").arg(LOG_ERROR));
                    socket->write(fileMaxRegistration.readAll());
                    ok = false;
                }
                else
                {
                    win.logMsg(QObject::tr("%1 TCP: Creating new user '%2' in database").arg(LOG_INFO).arg(username));
                    Player* newPlayer = new Player;
                    newPlayer->name = username;
                    newPlayer->passhash = passhash;
                    newPlayer->IP = socket->peerAddress().toString();
                    newPlayer->isConnected = false; // The Connection checks are done by the game Servers

                    tcpPlayers << newPlayer;
                    if (!Player::savePlayers(tcpPlayers)) ok = false;
                }
            }
            else // Found player, compare passhashes, check if already connected
            {
                if (player->passhash != passhash) // Bad password
                {
                    win.logMsg(QObject::tr("%1 TCP: Login failed, wrong password").arg(LOG_INFO));
                    socket->write(fileBadPassword.readAll());
                    socket->close();
                    ok = false;
                }
                /*
                else if (newPlayer.connected) // Already connected
                {
                    logMessage("TCP: Login failed, player already connected");
                    socket->write(fileAlready.readAll());
                    ok=false;
                }
                */
                else // Good Password
                {
                    /*
                    // Check too many connected
                    int n=0;
                    for (int i=0;i<tcpPlayers.size();i++)
                        if (tcpPlayers[i].connected)
                            n++;
                    if (n>=maxConnected)
                    {
                        logMessage("TCP: Login failed, too much players connected");
                        socket->write(fileMaxConnected.readAll());
                        ok=false;
                    }
                    else
                    */
                    {
                        //player->reset();
                        player->IP = socket->peerAddress().toString();
                        player->lastPingTime = timestampNow();
                        player->isConnected = true;
                    }
                }
            }

            if (ok) // Send Servers List
            {
                // HTTP reply template
                static const QByteArray data1 = QByteArray::fromHex("0D0A61757468726573706F6E73653A0A747275650A");
#if USE_BABSCON_CLIENT
                static const QByteArray data2 = QByteArray::fromHex("0A310A");
#elif USE_BRONYCON_CLIENT
                static const QByteArray data2 = QByteArray::fromHex("0A340A310A");
#endif
                static const QByteArray data3 = QByteArray::fromHex("0D0A300D0A0D0A");

                QByteArray customData = file.readAll();
                QByteArray sesskey = QCryptographicHash::hash(QString(passhash + Settings::saltPassword).toLatin1(), QCryptographicHash::Md5).toHex();

                //win.logMsg("[INFO] TCP: Hash of '"+QString(passhash + Settings::saltPassword).toLatin1()+"' is '"+sesskey+"'");
                //win.logMsg("[INFO] TCP: Sesskey is '"+sesskey+"', passhash is '"+passhash+"', salt is '"+saltPassword+"'");

                sesskey += passhash;
                QByteArray serversList;
                QByteArray line;
                do
                {
                    line = fileServersList.readLine().trimmed();
                    serversList += line;
                    serversList += 0x0A;
                } while (!line.isEmpty());

                serversList = serversList.trimmed();
                int dataSize = data1.size() + sesskey.size() + data2.size() + serversList.size() - 2;
                QString dataSizeStr = QString().setNum(dataSize, 16);

                customData += dataSizeStr;
                customData += data1;
                customData += sesskey;
                customData += data2;
                customData += serversList;
                customData += data3;

                win.logMsg(QObject::tr("%1 TCP: Login successful, sending servers list").arg(LOG_INFO));
                socket->write(customData);
                socket->close();
            }
        }
    }
    else if (data.contains("commfunction=removesession"))
    {
        win.logMsg(QObject::tr("%1 TCP: Session closed by client").arg(LOG_INFO));
    }
    else // Unknown request, erase tcp buffer
    {
        win.logMsg(QObject::tr("%1 TCP: Unknown request received: \n%2").arg(LOG_INFO).arg(QString(data.data())));
    }
}
