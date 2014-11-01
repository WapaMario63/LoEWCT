/********************************************************************************
** Form generated from reading UI file 'serverSettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERSETTINGSWIDGET_H
#define UI_SERVERSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverSettings
{
public:
    QTabWidget *tabServerSettingsWidget;
    QWidget *tabGeneral;
    QGroupBox *groupBox;
    QCheckBox *cbxEnableLogInServer;
    QCheckBox *cbxEnableGameServer;
    QLabel *lblMaxPlayersOnline;
    QSpinBox *spbMaxPlayersOnline;
    QGroupBox *groupBox_2;
    QCheckBox *cbxLogInfoMsgs;
    QFrame *line_5;
    QWidget *tabLogInServer;
    QGroupBox *groupBox_3;
    QLabel *lblLogInPort;
    QSpinBox *spbLogInPort;
    QPushButton *btnResetLogInPort;
    QLabel *lblMaxPlayersRegistered;
    QSpinBox *spbMaxPlayersRegistered;
    QPushButton *btnResetMaxPlayersRegistered;
    QFrame *line_2;
    QCheckBox *cbxEnableGetLog;
    QWidget *tab;
    QGroupBox *groupBox_4;
    QSpinBox *spbGamePort;
    QLabel *lblGamePort;
    QPushButton *btnResetGamePort;
    QFrame *line_3;
    QCheckBox *cbxSyncPlayers;
    QCheckBox *cbxSessionKeyValid;
    QLabel *lblSyncInterval;
    QSpinBox *spbPlayerSync;
    QLabel *lblPingTimeoutInterval;
    QSpinBox *spbPingTimeout;
    QSpinBox *spbPingInterval;
    QLabel *lblPingInterval;
    QPushButton *btnResetSyncInterval;
    QPushButton *btnResetPingTimeout;
    QPushButton *btnResetPingInterval;
    QGroupBox *groupBox_5;
    QCheckBox *checkBox;
    QLabel *label_2;
    QSpinBox *spinBox;
    QPushButton *pushButton_2;
    QCheckBox *checkBox_2;
    QFrame *line_7;
    QLabel *label;
    QWidget *tabAdv;
    QGroupBox *groupBox_7;
    QComboBox *cbxLoginServerThread;
    QComboBox *cbxGameServerThread;
    QLabel *lblLoginServerThread;
    QLabel *label_6;
    QLabel *lblLoginServerThread_2;
    QFrame *line_4;
    QCheckBox *ckbUseThreads;
    QFrame *line_6;
    QGroupBox *groupBox_6;
    QSpinBox *spinBox_3;
    QLabel *label_8;
    QPushButton *btnResetMaxPackets;
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton;

    void setupUi(QWidget *serverSettings)
    {
        if (serverSettings->objectName().isEmpty())
            serverSettings->setObjectName(QStringLiteral("serverSettings"));
        serverSettings->resize(647, 480);
        tabServerSettingsWidget = new QTabWidget(serverSettings);
        tabServerSettingsWidget->setObjectName(QStringLiteral("tabServerSettingsWidget"));
        tabServerSettingsWidget->setGeometry(QRect(10, 10, 626, 431));
        tabServerSettingsWidget->setTabPosition(QTabWidget::North);
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QStringLiteral("tabGeneral"));
        groupBox = new QGroupBox(tabGeneral);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 601, 91));
        cbxEnableLogInServer = new QCheckBox(groupBox);
        cbxEnableLogInServer->setObjectName(QStringLiteral("cbxEnableLogInServer"));
        cbxEnableLogInServer->setGeometry(QRect(10, 20, 281, 21));
        cbxEnableLogInServer->setChecked(true);
        cbxEnableGameServer = new QCheckBox(groupBox);
        cbxEnableGameServer->setObjectName(QStringLiteral("cbxEnableGameServer"));
        cbxEnableGameServer->setGeometry(QRect(310, 20, 281, 21));
        cbxEnableGameServer->setChecked(true);
        lblMaxPlayersOnline = new QLabel(groupBox);
        lblMaxPlayersOnline->setObjectName(QStringLiteral("lblMaxPlayersOnline"));
        lblMaxPlayersOnline->setGeometry(QRect(10, 60, 291, 21));
        spbMaxPlayersOnline = new QSpinBox(groupBox);
        spbMaxPlayersOnline->setObjectName(QStringLiteral("spbMaxPlayersOnline"));
        spbMaxPlayersOnline->setGeometry(QRect(310, 60, 281, 22));
        spbMaxPlayersOnline->setWrapping(false);
        spbMaxPlayersOnline->setFrame(true);
        spbMaxPlayersOnline->setReadOnly(false);
        spbMaxPlayersOnline->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spbMaxPlayersOnline->setAccelerated(false);
        spbMaxPlayersOnline->setKeyboardTracking(true);
        spbMaxPlayersOnline->setMaximum(999);
        spbMaxPlayersOnline->setValue(256);
        groupBox_2 = new QGroupBox(tabGeneral);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 110, 601, 51));
        cbxLogInfoMsgs = new QCheckBox(groupBox_2);
        cbxLogInfoMsgs->setObjectName(QStringLiteral("cbxLogInfoMsgs"));
        cbxLogInfoMsgs->setGeometry(QRect(10, 20, 581, 17));
        cbxLogInfoMsgs->setChecked(true);
        line_5 = new QFrame(tabGeneral);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(10, 50, 601, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        tabServerSettingsWidget->addTab(tabGeneral, QString());
        tabLogInServer = new QWidget();
        tabLogInServer->setObjectName(QStringLiteral("tabLogInServer"));
        groupBox_3 = new QGroupBox(tabLogInServer);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 601, 121));
        lblLogInPort = new QLabel(groupBox_3);
        lblLogInPort->setObjectName(QStringLiteral("lblLogInPort"));
        lblLogInPort->setGeometry(QRect(15, 60, 231, 20));
        spbLogInPort = new QSpinBox(groupBox_3);
        spbLogInPort->setObjectName(QStringLiteral("spbLogInPort"));
        spbLogInPort->setGeometry(QRect(300, 60, 211, 22));
        spbLogInPort->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spbLogInPort->setMaximum(999999);
        spbLogInPort->setValue(1034);
        btnResetLogInPort = new QPushButton(groupBox_3);
        btnResetLogInPort->setObjectName(QStringLiteral("btnResetLogInPort"));
        btnResetLogInPort->setGeometry(QRect(520, 60, 71, 23));
        lblMaxPlayersRegistered = new QLabel(groupBox_3);
        lblMaxPlayersRegistered->setObjectName(QStringLiteral("lblMaxPlayersRegistered"));
        lblMaxPlayersRegistered->setGeometry(QRect(15, 90, 271, 21));
        spbMaxPlayersRegistered = new QSpinBox(groupBox_3);
        spbMaxPlayersRegistered->setObjectName(QStringLiteral("spbMaxPlayersRegistered"));
        spbMaxPlayersRegistered->setGeometry(QRect(300, 90, 211, 22));
        spbMaxPlayersRegistered->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spbMaxPlayersRegistered->setMaximum(9999999);
        spbMaxPlayersRegistered->setValue(4096);
        btnResetMaxPlayersRegistered = new QPushButton(groupBox_3);
        btnResetMaxPlayersRegistered->setObjectName(QStringLiteral("btnResetMaxPlayersRegistered"));
        btnResetMaxPlayersRegistered->setGeometry(QRect(520, 90, 71, 23));
        line_2 = new QFrame(groupBox_3);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 40, 601, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        cbxEnableGetLog = new QCheckBox(groupBox_3);
        cbxEnableGetLog->setObjectName(QStringLiteral("cbxEnableGetLog"));
        cbxEnableGetLog->setGeometry(QRect(10, 20, 201, 17));
        cbxEnableGetLog->setChecked(false);
        tabServerSettingsWidget->addTab(tabLogInServer, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 10, 601, 181));
        spbGamePort = new QSpinBox(groupBox_4);
        spbGamePort->setObjectName(QStringLiteral("spbGamePort"));
        spbGamePort->setGeometry(QRect(300, 60, 211, 22));
        spbGamePort->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spbGamePort->setMaximum(999999);
        spbGamePort->setValue(1039);
        lblGamePort = new QLabel(groupBox_4);
        lblGamePort->setObjectName(QStringLiteral("lblGamePort"));
        lblGamePort->setGeometry(QRect(15, 60, 231, 20));
        btnResetGamePort = new QPushButton(groupBox_4);
        btnResetGamePort->setObjectName(QStringLiteral("btnResetGamePort"));
        btnResetGamePort->setGeometry(QRect(520, 60, 71, 23));
        line_3 = new QFrame(groupBox_4);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 40, 601, 21));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        cbxSyncPlayers = new QCheckBox(groupBox_4);
        cbxSyncPlayers->setObjectName(QStringLiteral("cbxSyncPlayers"));
        cbxSyncPlayers->setGeometry(QRect(10, 20, 181, 21));
        cbxSyncPlayers->setChecked(true);
        cbxSessionKeyValid = new QCheckBox(groupBox_4);
        cbxSessionKeyValid->setObjectName(QStringLiteral("cbxSessionKeyValid"));
        cbxSessionKeyValid->setGeometry(QRect(300, 20, 291, 21));
        cbxSessionKeyValid->setChecked(true);
        lblSyncInterval = new QLabel(groupBox_4);
        lblSyncInterval->setObjectName(QStringLiteral("lblSyncInterval"));
        lblSyncInterval->setGeometry(QRect(15, 90, 231, 20));
        spbPlayerSync = new QSpinBox(groupBox_4);
        spbPlayerSync->setObjectName(QStringLiteral("spbPlayerSync"));
        spbPlayerSync->setGeometry(QRect(300, 90, 211, 22));
        spbPlayerSync->setMaximum(9999999);
        spbPlayerSync->setValue(200);
        lblPingTimeoutInterval = new QLabel(groupBox_4);
        lblPingTimeoutInterval->setObjectName(QStringLiteral("lblPingTimeoutInterval"));
        lblPingTimeoutInterval->setGeometry(QRect(15, 120, 231, 20));
        spbPingTimeout = new QSpinBox(groupBox_4);
        spbPingTimeout->setObjectName(QStringLiteral("spbPingTimeout"));
        spbPingTimeout->setGeometry(QRect(300, 120, 211, 22));
        spbPingTimeout->setMaximum(999999);
        spbPingTimeout->setValue(25);
        spbPingInterval = new QSpinBox(groupBox_4);
        spbPingInterval->setObjectName(QStringLiteral("spbPingInterval"));
        spbPingInterval->setGeometry(QRect(300, 150, 211, 22));
        spbPingInterval->setMaximum(999999);
        spbPingInterval->setValue(3000);
        lblPingInterval = new QLabel(groupBox_4);
        lblPingInterval->setObjectName(QStringLiteral("lblPingInterval"));
        lblPingInterval->setGeometry(QRect(15, 150, 171, 20));
        btnResetSyncInterval = new QPushButton(groupBox_4);
        btnResetSyncInterval->setObjectName(QStringLiteral("btnResetSyncInterval"));
        btnResetSyncInterval->setGeometry(QRect(520, 90, 71, 23));
        btnResetPingTimeout = new QPushButton(groupBox_4);
        btnResetPingTimeout->setObjectName(QStringLiteral("btnResetPingTimeout"));
        btnResetPingTimeout->setGeometry(QRect(520, 120, 71, 23));
        btnResetPingInterval = new QPushButton(groupBox_4);
        btnResetPingInterval->setObjectName(QStringLiteral("btnResetPingInterval"));
        btnResetPingInterval->setGeometry(QRect(520, 150, 71, 23));
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 200, 601, 91));
        checkBox = new QCheckBox(groupBox_5);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(10, 20, 281, 17));
        label_2 = new QLabel(groupBox_5);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 60, 261, 20));
        spinBox = new QSpinBox(groupBox_5);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(300, 60, 211, 22));
        spinBox->setMaximum(99999);
        spinBox->setValue(10);
        pushButton_2 = new QPushButton(groupBox_5);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(520, 60, 71, 23));
        checkBox_2 = new QCheckBox(groupBox_5);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(300, 20, 291, 20));
        line_7 = new QFrame(groupBox_5);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(0, 40, 601, 21));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 369, 601, 31));
        label->setAlignment(Qt::AlignCenter);
        tabServerSettingsWidget->addTab(tab, QString());
        tabAdv = new QWidget();
        tabAdv->setObjectName(QStringLiteral("tabAdv"));
        groupBox_7 = new QGroupBox(tabAdv);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 10, 601, 181));
        cbxLoginServerThread = new QComboBox(groupBox_7);
        cbxLoginServerThread->setObjectName(QStringLiteral("cbxLoginServerThread"));
        cbxLoginServerThread->setGeometry(QRect(310, 120, 281, 22));
        cbxGameServerThread = new QComboBox(groupBox_7);
        cbxGameServerThread->setObjectName(QStringLiteral("cbxGameServerThread"));
        cbxGameServerThread->setGeometry(QRect(310, 150, 281, 22));
        cbxGameServerThread->setEditable(false);
        lblLoginServerThread = new QLabel(groupBox_7);
        lblLoginServerThread->setObjectName(QStringLiteral("lblLoginServerThread"));
        lblLoginServerThread->setGeometry(QRect(10, 120, 291, 21));
        label_6 = new QLabel(groupBox_7);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 20, 561, 41));
        lblLoginServerThread_2 = new QLabel(groupBox_7);
        lblLoginServerThread_2->setObjectName(QStringLiteral("lblLoginServerThread_2"));
        lblLoginServerThread_2->setGeometry(QRect(10, 150, 291, 21));
        line_4 = new QFrame(groupBox_7);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(0, 60, 601, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        ckbUseThreads = new QCheckBox(groupBox_7);
        ckbUseThreads->setObjectName(QStringLiteral("ckbUseThreads"));
        ckbUseThreads->setGeometry(QRect(10, 80, 581, 17));
        ckbUseThreads->setChecked(true);
        line_6 = new QFrame(groupBox_7);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(0, 100, 601, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        groupBox_6 = new QGroupBox(tabAdv);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 200, 601, 51));
        spinBox_3 = new QSpinBox(groupBox_6);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(291, 20, 221, 22));
        spinBox_3->setMaximum(999999);
        spinBox_3->setValue(100);
        label_8 = new QLabel(groupBox_6);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 20, 271, 21));
        btnResetMaxPackets = new QPushButton(groupBox_6);
        btnResetMaxPackets->setObjectName(QStringLiteral("btnResetMaxPackets"));
        btnResetMaxPackets->setGeometry(QRect(520, 20, 71, 23));
        tabServerSettingsWidget->addTab(tabAdv, QString());
        buttonBox = new QDialogButtonBox(serverSettings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(383, 445, 251, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);
        pushButton = new QPushButton(serverSettings);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 450, 131, 23));

        retranslateUi(serverSettings);

        tabServerSettingsWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(serverSettings);
    } // setupUi

    void retranslateUi(QWidget *serverSettings)
    {
        serverSettings->setWindowTitle(QApplication::translate("serverSettings", "Server Settings", 0));
        groupBox->setTitle(QApplication::translate("serverSettings", "General", 0));
        cbxEnableLogInServer->setText(QApplication::translate("serverSettings", "Enable Log In Server", 0));
        cbxEnableGameServer->setText(QApplication::translate("serverSettings", "Enable Game Server", 0));
        lblMaxPlayersOnline->setText(QApplication::translate("serverSettings", "Maximun Players Connected", 0));
        spbMaxPlayersOnline->setSpecialValueText(QString());
        groupBox_2->setTitle(QApplication::translate("serverSettings", "Server Console", 0));
        cbxLogInfoMsgs->setText(QApplication::translate("serverSettings", "Log Info Messages", 0));
        tabServerSettingsWidget->setTabText(tabServerSettingsWidget->indexOf(tabGeneral), QApplication::translate("serverSettings", "General Settings", 0));
        groupBox_3->setTitle(QApplication::translate("serverSettings", "General", 0));
        lblLogInPort->setText(QApplication::translate("serverSettings", "Log In Server Port ", 0));
        btnResetLogInPort->setText(QApplication::translate("serverSettings", "Reset", 0));
        lblMaxPlayersRegistered->setText(QApplication::translate("serverSettings", "Maximun Players Registered", 0));
        btnResetMaxPlayersRegistered->setText(QApplication::translate("serverSettings", "Reset", 0));
        cbxEnableGetLog->setText(QApplication::translate("serverSettings", "Enable GetLog (Advanced)", 0));
        tabServerSettingsWidget->setTabText(tabServerSettingsWidget->indexOf(tabLogInServer), QApplication::translate("serverSettings", "Log In Server", 0));
        groupBox_4->setTitle(QApplication::translate("serverSettings", "General", 0));
        lblGamePort->setText(QApplication::translate("serverSettings", "Game Server Port ", 0));
        btnResetGamePort->setText(QApplication::translate("serverSettings", "Reset", 0));
        cbxSyncPlayers->setText(QApplication::translate("serverSettings", "Sync Players (EnableMultiplayer)", 0));
        cbxSessionKeyValid->setText(QApplication::translate("serverSettings", "Enable Session Key Validation", 0));
        lblSyncInterval->setText(QApplication::translate("serverSettings", "Player Sync Interval", 0));
        spbPlayerSync->setSuffix(QApplication::translate("serverSettings", "ms", 0));
        lblPingTimeoutInterval->setText(QApplication::translate("serverSettings", "Player Ping Timeout", 0));
        spbPingTimeout->setSuffix(QApplication::translate("serverSettings", "s", 0));
        spbPingInterval->setSuffix(QApplication::translate("serverSettings", "ms", 0));
        lblPingInterval->setText(QApplication::translate("serverSettings", "Ping Check Interval", 0));
        btnResetSyncInterval->setText(QApplication::translate("serverSettings", "Reset", 0));
        btnResetPingTimeout->setText(QApplication::translate("serverSettings", "Reset", 0));
        btnResetPingInterval->setText(QApplication::translate("serverSettings", "Reset", 0));
        groupBox_5->setTitle(QApplication::translate("serverSettings", "Gameplay", 0));
        checkBox->setText(QApplication::translate("serverSettings", "Enable PVP", 0));
        label_2->setText(QApplication::translate("serverSettings", "Roll Cooldown", 0));
        spinBox->setSuffix(QApplication::translate("serverSettings", "s", 0));
        pushButton_2->setText(QApplication::translate("serverSettings", "Reset", 0));
        checkBox_2->setText(QApplication::translate("serverSettings", "Allow all players to teleport to any map (!maptp)", 0));
        label->setText(QApplication::translate("serverSettings", "<html><head/><body><p>To change other gameplay features exclusive to [LoEWCT], please go to the [LoEWCT] Settings.</p></body></html>", 0));
        tabServerSettingsWidget->setTabText(tabServerSettingsWidget->indexOf(tab), QApplication::translate("serverSettings", "Game Server", 0));
        groupBox_7->setTitle(QApplication::translate("serverSettings", "Threading", 0));
        cbxLoginServerThread->clear();
        cbxLoginServerThread->insertItems(0, QStringList()
         << QApplication::translate("serverSettings", "Highest Priority (Realtime)", 0)
         << QApplication::translate("serverSettings", "High Priority", 0)
         << QApplication::translate("serverSettings", "Normal", 0)
         << QApplication::translate("serverSettings", "Low Priority", 0)
         << QApplication::translate("serverSettings", "Lowest Priority", 0)
        );
        cbxLoginServerThread->setCurrentText(QApplication::translate("serverSettings", "Normal", 0));
        cbxGameServerThread->clear();
        cbxGameServerThread->insertItems(0, QStringList()
         << QApplication::translate("serverSettings", "Highest Priority (Realtime)", 0)
         << QApplication::translate("serverSettings", "High Priority", 0)
         << QApplication::translate("serverSettings", "Normal", 0)
         << QApplication::translate("serverSettings", "Low Priority", 0)
         << QApplication::translate("serverSettings", "Lowest Priority", 0)
        );
        cbxGameServerThread->setCurrentText(QApplication::translate("serverSettings", "Normal", 0));
        lblLoginServerThread->setText(QApplication::translate("serverSettings", "Log In Server Thread", 0));
        label_6->setText(QApplication::translate("serverSettings", "<html><head/><body><p align=\"center\">This allows you to choose which Server should your CPU care about more and use more of its resources.</p><p align=\"center\">Keep them set on Normal if you are not sure. (Might need a server restart if changed)</p></body></html>", 0));
        lblLoginServerThread_2->setText(QApplication::translate("serverSettings", "Game Server Thread", 0));
        ckbUseThreads->setText(QApplication::translate("serverSettings", "Use Threading", 0));
        groupBox_6->setTitle(QApplication::translate("serverSettings", "Server Settings", 0));
        label_8->setText(QApplication::translate("serverSettings", "Maximun Packet Dups", 0));
        btnResetMaxPackets->setText(QApplication::translate("serverSettings", "Reset", 0));
        tabServerSettingsWidget->setTabText(tabServerSettingsWidget->indexOf(tabAdv), QApplication::translate("serverSettings", "Advanced", 0));
        pushButton->setText(QApplication::translate("serverSettings", "Reset All To Defaults", 0));
    } // retranslateUi

};

namespace Ui {
    class serverSettings: public Ui_serverSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERSETTINGSWIDGET_H
