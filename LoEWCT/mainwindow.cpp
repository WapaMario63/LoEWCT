#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusBar->showMessage("Server is not Running");
}

MainWindow::~MainWindow()
{
  delete ui;
}

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
