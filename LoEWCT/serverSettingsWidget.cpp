#include "serverSettingsWidget.h"
#include "ui_serverSettingsWidget.h"

serverSettings::serverSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverSettings)
{
    ui->setupUi(this);
}

serverSettings::~serverSettings()
{
    delete ui;
}
