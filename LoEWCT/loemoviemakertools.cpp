#include "loemoviemakertools.h"
#include "ui_loemoviemakertools.h"

loeMovieMakerTools::loeMovieMakerTools(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loeMovieMakerTools)
{
    ui->setupUi(this);
}

loeMovieMakerTools::~loeMovieMakerTools()
{
    delete ui;
}
