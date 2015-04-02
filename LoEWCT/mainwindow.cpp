#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loewct.h"
#include "threads.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //loeGameThread = new QThread(this);
    //loeLoginThread = new QThread(this);
    loeThread = new Threads();
    loeThread->moveToThread(&loeLoginThread);

    connect(loeThread, SIGNAL(loggedConsole(QString)), this, SLOT(onLoggedConsole(QString)));

    ui->statusBar->showMessage("Server is not Running");
    logMsg("[LoEWCT] ALPHA Version 1.0.0");
}

MainWindow::~MainWindow()
{
    delete ui;

    loeLoginThread.quit();
    loeLoginThread.exit();
    loeGameThread.quit();

}

// Threading (see threads.cpp and loewct.h)
void MainWindow::onLoggedConsole(QString txt)
{
    logMsg(txt);
}

void MainWindow::startLoginThread()
{
    if (Settings::enableLoginServer)
    {
        loeThread->runLoginServThread();

        loeLoginThread.start();
    }
}

void MainWindow::startGameThread()
{
    if (Settings::enableGameServer)
    {

    }
}

void MainWindow::stopLoginThread()
{

}

void MainWindow::stopGameThread()
{

}

// Servers
void MainWindow::startLoginServer(bool log)
{
    if (log)
    {
        logMsg("Starting Log In Server on port "+QString().setNum(Settings::loginPort));
        loe.startLoginServer();
    }
}

void MainWindow::startGameServer(bool log)
{
    if (log)
    {
        loe.startGameServer();
    }
}

// Logging and other GUI functions
void MainWindow::logMsg(QString msg)
{
    ui->consoleLog->appendPlainText(msg);
    ui->consoleLog->repaint();
}

void MainWindow::logStatusMsg(QString msg)
{
    ui->statusBar->showMessage(msg);
}

void MainWindow::logGlobalChat(QString msg)
{
    ui->logChatGlobal->appendPlainText(msg);
    ui->logChatGlobal->repaint();
}

void MainWindow::startup()
{

}

void MainWindow::shutdown()
{

}

// Button click functions and stuff
void MainWindow::on_btnClearConsoleLog_clicked()
{
    ui->consoleLog->clear();
}

void MainWindow::on_actionServer_Settings_triggered()
{
    servStgWin.show();
}

void MainWindow::on_btnPlayerControls_clicked()
{
    plyrCtrls.show();
}

void MainWindow::on_btnMovieMakerTools_clicked()
{
    lmm.show();
}

void MainWindow::on_actionSettings_triggered()
{
    loewctStgWin.show();
}

void MainWindow::on_btnLoginServer_clicked()
{
    if (ui->btnLoginServer->text() == "Start Log In Server")
    {
        ui->btnLoginServer->setText("Stop Log In Server");
        startLoginThread();
    }
    else if (ui->btnLoginServer->text() == "Stop Log In Server")
    {
        ui->btnLoginServer->setText("Start Log In Server");
        stopLoginThread();
    }
}
