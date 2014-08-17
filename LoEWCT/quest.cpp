#include "quest.h"

#include <QFile>

#include "loewct.h"
#include "message.h"
#include "serialize.h"
#include "settings.h"
//#include "items.h"


Quest::Quest(QString path, Player *Owner)
{
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        win.logMessage(QObject::tr("%1 %2 Error reading quest database.").arg(LOG_SEVERE, LOG_QUEST));
        loe.stopServer();
        throw std::exception();
    }

    QList<QString> lines = QString(QObject::tr(QObject::tr(file.readAll().replace('\r',"")).split('\n');

    owner = Owner;
    commands = new QList<QList<QString>>;
    name = new QString(QObject::tr(QObject::tr();
    desc = new QString(QObject::tr(QObject::tr();
    npc = new Pony(nullptr);
    npc->id = 0;
    npc->netviewId = 0;
    id = 0;
    state = 0;
    eip = 0;

    try
    {
        // Parse the metadata, add everything else as quest commands
        for (int i=0; i<lines.size(); i++)
        {
            QList<QString> line = lines[i].split(" ", QString::SkipEmptyParts);
            if (!line.size() || lines[i][0]=='#') continue;
            if (line[0] == "name:")
            {
                if (line.size() > 2)
                {
                    npc->name = lines[i].mid(line[0].size() + 1);
                }
                else throw QString(QObject::tr("%1 %2 Error reading name of quest %3").arg(LOG_ERROR, LOG_QUEST, path));
            }
            else if (line[0] == "scene:")
            {
                if (line.size() >= 2) npc->sceneName = lines[i].mid(line[0].size() + 1).toLower();
                else throw QString(QObject::tr("%1 %2 Error reading scene of quest %3").arg(LOG_ERROR, LOG_QUEST, path));
            }
            else if (line[0] == "ponyData:")
            {
                if (line.size() == 2)
                {
#if BABSCON_BUILD
                    npc->ponyData = QByteArray::fromBase64(line[i].toLatin1());
#endif
#if BRONYCON_BUILD
                    QByteArray ponyData = QByteArray::fromBase64(line[1].toLatin1());
                    /// Read the ponyData
                    unsigned strlen;
                    unsigned lensize=0;
                    {
                        unsigned char num3; int num=0, num2=0;
                        do {
                            num3 = ponyData[lensize]; lensize++;
                            num |= (num3 & 0x7f) << num2;
                            num2 += 7;
                        } while ((num3 & 0x80) != 0);
                        strlen = (uint) num;
                    }
                    int nameSize = strlen + lensize;
                    int ponyDataSize = ponyData.size() - nameSize;
                    if (ponyDataSize == 43)
                    {
                        win.logMessage(QString(QObject::tr(QObject::tr("[INFO] [QUESTSCRIPT] ponyData of quest %1 is in old BABScon format, converting...").arg(path));
                        ponyData += uint32ToData(0); // Member ID
                        ponyData.insert(nameSize+17+3, ponyData.mid(nameSize+17,3)); // Hair Color 2 (copy of color 1)
                    }
                    npc->ponyData = ponyData;
#endif
                }
                else throw QString(QObject::tr("%1 %2 Error reading ponyData of quest %3").arg(LOG_ERROR, LOG_QUEST, path));
            }
            else if (line[0] == "pos:")
            {
                if (line.size() == 4)
                {
                    bool ok1, ok2, ok3;
                    npc->pos = UVector(line[1].toFloat(&ok1), line[2].toFloat(&ok2), line[3].toFloat(&ok3));
                    if (!(ok1 && ok2 && ok3))
                        throw QString(QObject::tr("%1 %2 Error reading position of quest %3").arg(LOG_ERROR, LOG_QUEST, path));
                }
            }
            else if (line[0] == "rot:")
                if (line.size()==5)
                {
                    bool ok1, ok2, ok3, ok4;
                    npc->rot = UQuaternion(line[1].toFloat(&ok1), line[2].toFloat(&ok2),
                                            line[3].toFloat(&ok3), line[4].toFloat(&ok4));
                    if (!(ok1 && ok2 && ok3 && ok4))
                        throw QString(QObject::tr("[ERROR][QUESTSCRIPT] Error reading rot, quest ").arg(LOG_ERROR, LOG_QUEST, path));
                }
                else throw QString(QObject::tr("[ERROR][QUESTSCRIPT] Error reading rot, quest ").arg(LOG_ERROR, LOG_QUEST, path));
            else if (line[0] == "wear:")
            {
                for (int i=1; i<line.size(); i++)
                {
                    bool ok;
                    int itemId = line[i].toInt(&ok);
                    if (!ok)
                        throw QString(QObject::tr("[ERROR][QUESTSCRIPT] Error reading wear, quest ").arg(LOG_ERROR, LOG_QUEST, path));
                    WearableItem item;
                    item.id = itemId;
                    item.index = wearablePositionsToSlot(win.wearablePositionsMap[itemId]);
                    npc->worn << item;
                }
            }
            else if (line[0] == "shop")
              {
                // -> Jesus, I placed a 1 instead of an i in i<lines.size(); inside the for statement.
                // --> Ladies and Gentlemen, the biggest derp of all of [LoEWCT]'s development. For now. lel
                for (int i=1; i<line.size(); i++)
                  {
                    bool ok;
                    int itemId = line[i].toInt(&ok);
                    if(!ok)
                        throw QString(QObject::tr("[ERROR][QUESTSCRIPT] Error Reading shop, quest ").arg(LOG_ERROR, LOG_QUEST, path));
                    InventoryItem item;
                    item.id = itemId;
                    item.index = i-1;
                    item.amount = (quint32)-1;
                    npc->inv << item;
                  }
              }
            else if (line[0] == "questId")
                if (line.size()==2)
                {
                    id = line[1].toInt();

                    win.lastIdMutex.lock();
                    npc->id = 0;
                    npc->netviewId = id;
                    win.lastIdMutex.unlock();
                }
                else throw QString(QObject::tr("[ERROR][QUESTSCRIPT] Error reading questId, quest ").arg(LOG_ERROR, LOG_QUEST, path));
            else if (line[0] == "questName")
                if (line.size()>=2)
                    *name = lines[i].mid(line[0].size()+1);
                else throw QString(QObject::tr("[ERROR][QUESTSCRIPT] Error reading questName, quest ").arg(LOG_ERROR, LOG_QUEST, path));
            else if (line[0] == "questDescr")
                if (line.size()>=2)
                    *descr = lines[i].mid(line[0].size()+1);
                else throw QString(QObject::tr("[ERROR][QUESTSCRIPT] Error reading questDescr, quest ").arg(LOG_ERROR, LOG_QUEST, path));
            else
                commands->append(line);
        }
    }
    catch (QString& error)
    {
        win.logMessage(error);
        loe.stopServer(true);
    }
}

QString Quest::concatAfter(QList<QString> list, int id) const
{
    QString result;
    if (list.size() <= id) return result;
    result = list[id];
    for (int i=id+1; i<list.size(); i++) result += " " + list[i];
    return result;
}

int Quest::findLabel(QString label)
{
    for (int i=0; i<commands->size(); i++)
        if ((*commands)[i].size() == 2 && (*commands)[i][0] == "label :" && (*commands)[i][1].trimmed() == label.trimmed())
            return i;
    return -1;
}

void Quest::logError(QString msg)
{
    win.logMessage(QObject::tr("%1 Error running QuestScript %2, eip=%3 : %4").arg(LOG_ERROR, id, eip, msg));
}

void Quest::setOwner(Player *Owner)
{
    owner = Owner;
}

void Quest::runScript()
{
    runScript(0);
}

void Quest::runScript(int Eip)
{
    for (eip=Eip; eip < commands->size();)
    {
        if (doCommand(eip)) eip++;
        else break;
    }
}

bool Quest::doCommand(int commandEip)
{
    if (!owner)
    {
        win.logMessage(QObject::tr("%1 %2 doCommand called with no owner").arg(LOG_SEVERE, LOG_QUEST));
        return false;
    }

    //win.logMessage("Executing command "+QString().setNum(eip));

    QStringList command = (*commands)[commandEip];

    if (command[0] == "label :") return true;
    else if (command[0] == "goto ->")
    {
        if (command.size() != 2)
        {
            logError(QObject::tr("goto | takes exactly one argument"));
            return false;
        }
        int newEip = findLabel(command[1]);
        if (newEip == -1)
        {
            logError(QObject::tr("label not found"));
            return false;
        }
        eip = newEip;
    }
    else if (command[0] == "end()")
    {
        sendEndDialog(owner);
        return false;
    }
    else if (command[0] == "say:")
    {
        QString msg, npcName;
        QList<QString> answers;
        quint16 iconId = 0;
        bool hasIconUd = false;

        if (command.size() >= 2)
        {
            msg = concatAfter(command, 1);
            npcName = npc->name;
        }
        else
        {
            logError(QObject::tr("say | takes 2 arguments (say: message"));
            return false;
        }

        // Parse answers, icon and name
        for (int i=commandEip+1; i<commands->size(); i++)
        {
            if ((*commands)[i][0] == "answer (") answers << concatAfter((*commands)[i], 2);
            else if ((*commands)[i][0] == "sayName")
        }
    }
}
