#ifndef SERVERSETTINGSWIDGET_H
#define SERVERSETTINGSWIDGET_H

#include <QWidget>

namespace Ui {
class serverSettings;
}

class serverSettings : public QWidget
{
    Q_OBJECT

public:
    explicit serverSettings(QWidget *parent = 0);
    ~serverSettings();

private:
    Ui::serverSettings *ui;
};

extern serverSettings servStgWin;

#endif // SERVERSETTINGSWIDGET_H
