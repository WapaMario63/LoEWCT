#include "chat.h"

#include "player.h"
#include "pony.h"
#include "serialize.h"
#include "message.h"
#include "loewct.h"
#include "mainwindow.h"
#include "settings.h"

void receiveChatMessage(QByteArray msg, Player *player)
{
    QSettings config(LOEWCTCONFIGFILEPATH, QSettings::IniFormat);
    Settings::motdMessage = config.value("motdMsg", "Parties at Sugarcane Corner are always AWESOME! Why don't you join the party?").toString();
    Settings::rulesMessage = config.value("serverRules", "Server rules: \n1.No Swearing excesively \n2.Respect Others \n3.HAVE FUN!").toString();
    //Settings::helpMessage = config.value("helpMessage", "Welcome to our Legends of Equestria Server! \nType !?cmds to view some commands for this server.").toString(); // Deprecated
    Settings::serverPrefix = config.value("serverPrefix", "[LoEWCT]").toString();
    Settings::mapTpEnable = config.value("playerMapTp", false).toBool();
    Settings::rollCoolDown = config.value("rollCoolDown", 10).toInt();

    QString txt = dataToString(msg.mid(7));
    QString author = player->pony.name;
    win.logGlobalChat("["+author+"]: "+txt);

    if (txt.startsWith("/stuck") || txt.startsWith("unstuck me"))
    {
        sendLoadSceneRPC(player, player->pony.sceneName);
    }
    else if (txt.startsWith("!kill"))
    {
        QTimer *killTimer = new QTimer();
        killTimer->setSingleShot(true);

        QString deadPlayerName = player->name;
        QObject::connect(killTimer, &QTimer::timeout, [=]()
        {
            // Find the player again instead of reusing pointer, in case they disconnect
            Player* deadPlayer = Player::findPlayer(loe.udpPlayers, deadPlayerName);
            if (deadPlayer->isConnected && deadPlayer->pony.dead)
            {
                sendSetStatRPC(deadPlayer, 1, deadPlayer->pony.health);
                Scene* scene = findScene(deadPlayer->pony.sceneName);
                for (Player* other : scene->players)
                    sendNetviewInstantiate(&deadPlayer->pony, other);
                deadPlayer->pony.dead = false;
            }
            delete killTimer;
            // Don't delete deadPlayer here, that kills the player's session.
        });
        if (!player->pony.dead)
        {
            player->pony.dead = true;
            sendSetStatRPC(player, 1, 0);
            killTimer->start(Settings::anheroTime);
            Scene* scene = findScene(player->pony.sceneName);
            for (Player* other : scene->players)
                sendNetviewRemove(other, player->pony.netviewId, NetviewRemoveReasonKill);
        }
    }
    else if (txt.startsWith("!motd"))
    {
        sendMessageBox(player, Settings::motdMessage);
    }
    else if (txt.startsWith("!help"))
    {
        txt = txt.remove(0,6);
        if (txt.isEmpty() || txt == "1")
            sendChatMessage(player, "<span color=\"yellow\">Available commands (Page 1/2):</span><span color=\"orange\"><br/>!help - Shows this message <br/>!motd - Shows motd box<br/>!rules - Shows server rules<br/>!roll - Rolls a random number from 00-99<br/>!list - Shows list of players online (all maps)<br/>!me [action] - States your current action.<br/>--Do !help 2 for next page--</span>", Settings::serverPrefix, ChatSystem);
        else if (txt == "2")
            sendChatMessage(player, "<span color=\"yellow\">Available commands (Page 2/2):</span><span color=\"orange\"><br/>!msg [ponyName] [message] - Alternative to /whisper and /w. Send a Message to somepony. No spaces in ponyName.<br/>!plugins - Lists all the plugins the server uses.<br/>!info - Shows server information.", Settings::serverPrefix, ChatSystem);
        else if (txt.toInt() > 2)
            sendChatMessage(player, "<span color=\"yellow\">No more pages to show.</span>", Settings::serverPrefix, ChatSystem);
        else sendChatMessage(player, "<span color=\"orange\">Error: Syntax is: !help or !help [page]</span>", Settings::serverPrefix, ChatSystem);
    }
    else if (txt.startsWith("!msg"))
    {
        if (txt.count(" ") < 2)
            sendChatMessage(player, "<span color=\"orange\">Error: Syntax is: !msg [ponyName] [message]. ponyName is Case-Sensitive, no spaces on ponyName either.</span>", Settings::serverPrefix, ChatSystem);
        else
        {
            for (int i=0; i<loe.udpPlayers.size(); i++)
            {
                if (loe.udpPlayers[i]->inGame >= 2 && loe.udpPlayers[i]->pony.name.toLower().remove(" ").startsWith(txt.toLower().section(" ", 1, 1)))
                {
                    txt = txt.remove(0, txt.indexOf(" ", 5) + 1);
                    sendChatMessage(loe.udpPlayers[i], "<span color=\"yellow\">["+author+"-> You]</span> "+txt, author, ChatWhisper);
                    sendChatMessage(player, "<span color=\"yellow\">[You ->"+ loe.udpPlayers[i]->pony.name +"]</span> "+txt, author, ChatWhisper);
                }
            }
        }
    }
    else if (txt.startsWith("!list"))
    {
        QString nameList = "<span color=\"yellow\">Players currently ingame:</span>";
        for (int i=0; i<loe.udpPlayers.size(); i++)
        {
            if (loe.udpPlayers[i]->inGame >= 2)
            {
                nameList += "<span color=\"orange\">"+loe.udpPlayers[i]->pony.name+" ("+loe.udpPlayers[i]->name+") in map: "+loe.udpPlayers[i]->pony.sceneName+" </span>";
            }
            sendChatMessage(player, nameList, Settings::serverPrefix, ChatSystem);
        }
    }
    else // Broadcast their message
    {
        // Commands that broadcasts it set message
        int rollnum = -1;
        QString rollStr;
        bool actMsg = false;

        if (txt == ("!roll"))
        {
            if (player->chatRollCooldownEnd < QDateTime::currentDateTime())
            {
                rollnum = qrand() % 100;
                rollStr.sprintf("<<span color=\"yellow\">#b%s#b rolls %02d</span>", author.toLocal8Bit().data(), rollnum);
                player->chatRollCooldownEnd = QDateTime::currentDateTime().addSecs(Settings::rollCoolDown);
                /*if (player->chatRollCooldownEnd >= QDateTime::addSecs(0))
                {
                    sendChatMessage(player, "<span color=\"yellow\">You must wait "+ Settings::rollCoolDown +" seconds to roll again.</span>", Settings::serverPrefix, ChatSystem);
                }*/
            }
        }
        if (txt.startsWith("!me"))
        {
            actMsg = true;
            txt.remove(0,3);
            txt = "<em>#b <span color=\"yellow\">"+author+"</spann>#b <span color=\"cyan\">"+txt+"</span>";
        }
        if ((quint8)msg[6] == 8) // Local chat Only
        {
            Scene* scene = findScene(player->pony.sceneName);
            if (scene->name.isEmpty())
                win.logMsg("[ERROR] UDP: Can't find scene for chat message, aborting!");
            else
            {
                for (int i=0; i<scene->players.size(); i++)
                {
                    if (rollnum > -1) sendChatMessage(scene->players[i], rollStr, Settings::serverPrefix, ChatLocal);
                    else if (actMsg) sendChatMessage(scene->players[i], txt, "", ChatLocal);
                    else if (txt.startsWith(">")) sendChatMessage(scene->players[i], "<span color=\"green\">"+txt+"</span>", author, ChatLocal);
                    else sendChatMessage(scene->players[i], txt, author, ChatLocal);
                }
            }
        }
        else // Send on Global Chat
        {
            for (int i=0; i<loe.udpPlayers.size(); i++)
            {
                if (loe.udpPlayers[i]->inGame >= 2)
                {
                    if (rollnum) sendChatMessage(loe.udpPlayers[i], rollStr, Settings::serverPrefix, ChatGeneral);
                    else if (txt.startsWith(">")) sendChatMessage(loe.udpPlayers[i], "<span color=\"green\">"+txt+"</span>", author, ChatGeneral);

                    // Colored text parsers
                    else if (txt.startsWith("&0"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"black\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&1"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"navy\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&2"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"olive\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&3"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"teal\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&4"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"maroon\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&5"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"purple\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&6"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"orange\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&7"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"gray\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&8"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"gray\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&9"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"blue\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&a"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"green\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&b"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"aqua\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&c"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"red\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&d"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"magenta\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&e"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"yellow\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else if (txt.startsWith("&f"))
                    {
                        txt.remove(0,2);
                        sendChatMessage(loe.udpPlayers[i], "<span color=\"white\">"+txt+"</span>", author, ChatGeneral);
                    }
                    else sendChatMessage(loe.udpPlayers[i], txt, author, ChatGeneral);
                }
            }
        }
    }
}
