#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QWidget>

namespace Ui {
class playerControls;
}

class playerControls : public QWidget
{
    Q_OBJECT

public:
    explicit playerControls(QWidget *parent = 0);
    ~playerControls();

private:
    Ui::playerControls *ui;
};

extern playerControls plyrCtrls;

#endif // PLAYERCONTROLS_H
