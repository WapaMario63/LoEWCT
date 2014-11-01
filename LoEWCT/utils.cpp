#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loewct.h"

#if defined WIN32 || defined _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

void saveResourceToDataFolder(QString resRelPath)
{
    win.logMsg(QString("Saving player's data to: ")+resRelPath);
    QString dataPath = QDir::homePath()+"/AppData/LocalLow/LoE/Legends of Equestria/";
    QFile::remove(dataPath+resRelPath);
    QFile::copy(QString(":/gameFiles/")+resRelPath, dataPath+resRelPath);
    //SetFileAttributesA(QString(dataPath+resRelPath).toStdString().c_str(),FILE_ATTRIBUTE_NORMAL);
}

QByteArray removeHTTPHeader(QByteArray data,QString header)
{
    int i1 = data.indexOf(header);
    if (i1==-1) return data;
    int i2 = data.indexOf("\n", i1);
    if (i2==-1) return data;
    data.remove(i1, i2-i1+1);
    return data;
}

float timestampNow()
{
    time_t newtime;
#if defined WIN32 || defined _WIN32
    newtime = GetTickCount();
#elif defined __APPLE__
    timeval time;
    gettimeofday(&time, NULL);
    newtime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
#else
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);
    newtime = tp.tv_sec*1000 + tp.tv_nsec/1000/1000;
#endif
    return (float)(((float)(newtime - loe.startTimeStamp))/(float)1000); // Seconds since server start (startTimestamp)
}



char convertChar (char c, bool direction = true)
{
    if (direction)
    {
        if (c >= 'a' && c <= 'z')
        {
            return c - 'a';
        }
        if (c >= 'A' && c <= 'Z')
        {
            return c - 'A' + '\x1a';  // \u001a
        }
        if (c >= '0' && c <= '9')
        {
            return c - '0' + '4';
        }
        return '>';
    }
    else
    {
        if (c >= '\0' && c <= '\x19')  // \u0019
        {
            return c + 'a';
        }
        if (c >= '\x1a' && c <= '3')  // \u001a
        {
            return c + 'A' - '\x1a';  // u001a
        }
        if (c >= '4' && c <= '=')
        {
            return c + '0' - '4';
        }
        return ' ';
    }
}
