#include <QApplication>
#include <QTranslator>
#include <QDir>

#include "loewct.h"
#include "mainwindow.h"
#include "serverSettingsWidget.h"
#include "playercontrols.h"
#include "loemoviemakertools.h"
#include "loewctSettingsWidget.h"

int argc=0;

QApplication a(argc, (char**)0);

LoEWCT loe;
MainWindow win;
serverSettings servStgWin;
playerControls plyrCtrls;
loeMovieMakerTools lmm;
loewctSettings loewctStgWin;

QTextStream cout(stdout);
QTextStream cin(stdin);

int main(int, char**)
{
    // Windows DLL hell fix
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
    a.addLibraryPath("platforms");

    // Adds ability to use translations
    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    if (!translator.load("languages/"+locale))
    {
        win.logMsg("[QDebug] Unable to load language translation.");
    }
    else
    {
        win.logMsg("[QDebug] Langauge Translation Loaded.");
    }
    a.installTranslator(&translator);

    win.show();
    a.processEvents();

    return a.exec();
}
