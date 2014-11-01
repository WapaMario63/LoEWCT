#ifndef LOEWCTSETTINGSWIDGET_H
#define LOEWCTSETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class loewctSettings;
}

class loewctSettings : public QWidget
{
    Q_OBJECT

public:
    explicit loewctSettings(QWidget *parent = 0);
    ~loewctSettings();

private:
    Ui::loewctSettings *ui;
};

extern loewctSettings loewctStgWin;

#endif // LOEWCTSETTINGSWIDGET_H
