#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolBar>

#include "loewct.h"
#include "settings.h"

#if defined _WIN32 || defined WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chatBoxHandler();
}

void MainWindow::logStatus(QString msg)
{
    ui->consoleLog->appendPlainText(msg);
    ui->serverStatus->setText(msg);
    ui->consoleLog->repaint();
    ui->serverStatus->repaint();
}

void MainWindow::logMessage(QString msg)
{
    if (!Settings::logInfo) return;
    ui->consoleLog->appendPlainText(msg);
    ui->consoleLog->repaint();
}

void MainWindow::chatBoxHandler()
{
    // *Handle Chat Boxes in Local chat* \\

    // Hide all of these
    ui->chatLog_local_ctl->hide();
    ui->chatLog_local_pv->hide();
    ui->chatLog_local_cld->hide();
    ui->chatLog_local_gms->hide();

    // If this scene is selected, show it's local chat box.
    if (ui->sceneSelect_chat->currentTextChanged("ponyville"))
        ui->chatLog_local_pv->show();
    else if (ui->sceneSelect_chat->currentTextChanged("canterlot"))
        ui->chatLog_local_ctl->show();
    else if (ui->sceneSelect_chat->currentTextChanged("cloudsdale"))
        ui->chatLog_local_cld->show();
    else if (ui->sceneSelect_chat->currentTextChanged("gemmines"))
        ui->chatLog_local_gms->show();
}

MainWindow::~MainWindow()
{
    Settings::logInfo = false; // logMessage while we're trying to destroy would crash.

    for (;loe.udpPlayers.size;)
    {

    }
}
