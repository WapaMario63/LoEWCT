#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loewct.h"

#if defined _WIN32 || defined WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
{

}

MainWindow::~MainWindow()
{
  delete ui;
}
