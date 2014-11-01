#include "loewctSettingsWidget.h"
#include "ui_loewctSettingsWidget.h"

loewctSettings::loewctSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loewctSettings)
{
    ui->setupUi(this);
}

loewctSettings::~loewctSettings()
{
    delete ui;
}
