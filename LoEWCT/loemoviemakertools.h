#ifndef LOEMOVIEMAKERTOOLS_H
#define LOEMOVIEMAKERTOOLS_H

#include <QWidget>

namespace Ui {
class loeMovieMakerTools;
}

class loeMovieMakerTools : public QWidget
{
    Q_OBJECT

public:
    explicit loeMovieMakerTools(QWidget *parent = 0);
    ~loeMovieMakerTools();

private:
    Ui::loeMovieMakerTools *ui;
};

extern loeMovieMakerTools lmm;

#endif // LOEMOVIEMAKERTOOLS_H
