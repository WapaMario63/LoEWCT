#ifndef QUEST_H
#define QUEST_H

#include <QString>
#include <QList>

// This file handles the quest system and the QuestScript+ Scripting language

class Player;
class Pony;

// Quests are bound to one NPC
// They define the NPC, what he say, and the reactions.

struct Quest
{
public:
    Quest(QString path, Player* Owner);

    void runScript(); // Runs a QuestSCript from the start, until the end or the next dialog

    bool doCommand(int commandEip); // Runs QuestScript Syntax, returns false if we should stop running the script (e.g. because we are waiting for an answer)
    void processAnswer(int answer); // Called when client picks an answer in a dialog.
    void processAnswer(); // Called when a client clicks on a dialog with no proposed answer.

    int findLabel(QString label); // Returns the eip of this label

    void logError(QString msg); // Simply logs any errors when running a quest script
    void setOwner(Player* Owner);

private:
    void runScript(int Eip); // runs the script until the end or the next dialog
    QString concatAfter(QList<QString> list, int id) const; // Concatenate the strings after id in the list

public:
    QList<QList<QString>>* commands; // List of commands/syntax and their arguments, parsed from the quest file.
    quint16 eip; // Instruction pointer inside the commands.
    quint16 state; // State (progess) of the quest.
    quint16 id; // Unique id of the quest.
    QString* name; // Name of the quest.
    QString* desc; // Description of the quest.
    Pony* npc; // NPC of this quest's script
    Player* owner; // Player who owns this wuest save/runs the script
};

#endif // QUEST_H
