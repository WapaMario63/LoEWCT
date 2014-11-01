#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "serverSettingsWidget.h"
#include "playercontrols.h"
#include "loemoviemakertools.h"
#include "loewctSettingsWidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;

    void logMsg(QString msg);
    void logStatusMsg(QString msg);
    void command(QString cmd);
    void logGlobalChat(QString msg);

    // Used to call loewct class
    void stopLogInServer(bool log);
    void stopGameServer(bool log);

    void startup(); // Starts the application without affecting server.

public slots:
    void shutdown(); // Shutsdown the application, affecting server to stop.

private slots:
    void on_btnClearConsoleLog_clicked();

    void on_actionServer_Settings_triggered();

    void on_btnPlayerControls_clicked();

    void on_btnMovieMakerTools_clicked();

    void on_actionSettings_triggered();
};

extern MainWindow win;

#endif // MAINWINDOW_H
