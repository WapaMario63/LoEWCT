#include "mobparser.h"

#include <QString>
#include <QStringList>

#include "mob.h"
#include "mobzone.h"
#include "loewct.h"
#include "settings.h"

void parseMobzoneData(QByteArray data)
{
    QStringList lines = QString(data).replace('\r',"").split('\n');

    Mobzone* zone = new Mobzone;

    //bool gotStart = false, gotEnd = false; // True when we have the start/end bounds

    for (QString line : lines)
      {
        // Skip empty lines and comments
        if (!line.size() || line[0]=='#')
          continue;

        if (line.startsWith("startPos: "))
          {
            QStringList coords = line.mid(10).split(' ');
            if (coords.size() != 3)
              throw QString(LOG_SEVERE+QObject::tr("parseMobzoneData Error: error reading start position (syntax error?)."));

            bool ok1, ok2, ok3;
            float x = coords[0].toFloat(&ok1);
            float y = coords[1].toFloat(&ok2);
            float z = coords[2].toFloat(&ok3);
            if (!ok1 || !ok2 || !ok3)
              throw QString(LOG_SEVERE+QObject::tr("parseMobzoneData Error: error reading start position (syntax error?)."));

            zone->start = UVector{x,y,z};

            /*gotStart = true;
            if (gotEnd)
              {
                // "Normalize" the bounds. The start gets the smaller coordinates, the end gets the bigger
                UVector newStart = {std::min(zone->start.x, zone->end.x),
                                    std::min(zone->start.y, zone->end.y),
                                    std::min(zone->start.z, zone->end.z)};
                UVector newEnd = {std::max(zone->start.x, zone->end.x),
                                  std::max(zone->start.y, zone->end.y),
                                  std::max(zone->start.z, zone->end.z)};
                zone->start = newStart;
                zone->end = newEnd;
              }*/
          }
        else if (line.startsWith("endPos: "))
          {
            QStringList coords = line.mid(8).split(' ');
            if (coords.size() != 3)
              throw QString(LOG_SEVERE+QObject::tr("parseMobzoneData Error: error reading end position (syntax error?)."));

            bool ok1, ok2, ok3;
            float x = coords[0].toFloat(&ok1);
            float y = coords[1].toFloat(&ok2);
            float z = coords[2].toFloat(&ok3);
            if (!ok1 || !ok2 || !ok3)
              throw QString(LOG_SEVERE+QObject::tr("parseMobzoneData Error: error reading start position (syntax error?)."));

            zone->end = UVector{x,y,z};

            /*gotEnd = true;
            if (gotStart)
              {
                // "Normalize" the bounds. The Start gets the smaller coordinates, the end the bigger
                UVector newStart = {std::min(zone->start.x, zone->end.x),
                                    std::min(zone->start.y, zone->end.y),
                                    std::min(zone->start.z, zone->end.z)};
                UVector newEnd = {std::max(zone->start.x, zone->end.x),
                                  std::max(zone->start.x, zone->end.y),
                                  std::max(zone->start.z, zone->end.z)};
                zone->start = newStart;
                zone->end = newEnd;
              }*/
          }
        else if (line.startsWith("scene: "))
          {
            line = line.mid(7);
            zone->sceneName = line;
          }
        else if (line.startsWith("mob: "))
          {
            line = line.mid(5);
            Mob* mob = new Mob(zone);
            QStringList args = line.split(',');
            for (QString arg : args)
              {
                QStringList keyValuePair = arg.split('=');
                if (keyValuePair.size() != 2)
                  throw QString(LOG_SEVERE+QObject::tr("parseMobzoneData Error: error reading mob key/value pair (syntax error?)."));
                QString key = keyValuePair[0].trimmed();
                QString value = keyValuePair[1].trimmed();

                if (key=="type")
                  mob->setType("mobs/"+value);
                else
                  throw QString(LOG_SEVERE+QObject::tr("parseMobzoneData Error: error reading mob argument, unknown argument ")+key);
                loe.mobs << mob;
              }
          }
        else
          {
            throw QString(LOG_SEVERE+QObject::tr("parseMobzoneData Error: unknown statement ")+line);
          }
     }

    loe.mobzones << zone;
}
