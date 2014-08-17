#include "mainwindow.h"
#include <QApplication>

#include <QTranslator>
#include <QDir>

#include "LuaSrc/lua.hpp"
#include "loewct.h"

int argc=0;

QApplication a(argc, (char**)0);
MainWindow win;
LoEWCT loe;

int main(int, char**)
{
    // Windows DLL hell fix
    QCoreApplication::addLibraryPath(QCoreApplication::applicationDirPath());
    a.addLibraryPath("platforms");

    // Add Capatability for language translations
    QString locale = QLocale::system().name().section('_', 0, 0);

    QTranslator translator;
    if(!translator.load("languages/"+locale))
    {
        qDebug() << "Unable to load language translation";
    }

    a.installTranslator(&translator);

    // Start windows and Processes
    win.show();
    a.processEvents();

    // Start the server


    // Window's dtor will quick_exit (we don't run the atexits)
    return a.exec();
}
