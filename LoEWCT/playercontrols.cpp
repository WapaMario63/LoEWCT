#include "playercontrols.h"
#include "ui_playercontrols.h"

playerControls::playerControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playerControls)
{
    ui->setupUi(this);
}

playerControls::~playerControls()
{
    delete ui;
}
