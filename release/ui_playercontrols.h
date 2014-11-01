/********************************************************************************
** Form generated from reading UI file 'playercontrols.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERCONTROLS_H
#define UI_PLAYERCONTROLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playerControls
{
public:
    QLabel *lblWinInfo;
    QFrame *line;
    QGroupBox *groupBox;
    QLineEdit *txtSendGUIMsg;
    QPushButton *btnSendGUIMsg;
    QComboBox *cmbMapSelect;
    QPushButton *btnMapTP;
    QLineEdit *txtTpPlayerID1;
    QLineEdit *txtTpPlayerID2;
    QPushButton *btnTpPlayerByID;
    QLineEdit *txtTpPlayerX;
    QLineEdit *txtTpPlayerZ;
    QLineEdit *txtTpPlayerY;
    QPushButton *btnTpPlayerByCoord;
    QGroupBox *groupBox_2;
    QLineEdit *txtKickPlayerMsg;
    QPushButton *btnKickPlayer;
    QLineEdit *txtBanPlayerMsg;
    QPushButton *btnBanPlayer;
    QPushButton *btnPromoteToMod;
    QPushButton *btnDemoteToPlayer;
    QFrame *line_2;
    QPushButton *btnMutePlayer;
    QPushButton *btnUnmutePlayer;
    QGroupBox *groupBox_3;
    QPushButton *btnGetPlayerPos;
    QPushButton *btnGetPlayerRot;
    QPushButton *btnGetPlayerPonyData;
    QLineEdit *txtPlayerInfoResult;
    QFrame *line_3;
    QGroupBox *groupBox_4;
    QLineEdit *txtAnnouncementMsg;
    QLabel *lblAnnouncementMsg;
    QLabel *lblAnnoucementMsgLenght;
    QDoubleSpinBox *spbAnnoucementLenght;
    QPushButton *pushButton;
    QPushButton *btnSendAnnouncement;

    void setupUi(QWidget *playerControls)
    {
        if (playerControls->objectName().isEmpty())
            playerControls->setObjectName(QStringLiteral("playerControls"));
        playerControls->resize(431, 622);
        playerControls->setMaximumSize(QSize(431, 4000000));
        playerControls->setSizeIncrement(QSize(431, 460));
        lblWinInfo = new QLabel(playerControls);
        lblWinInfo->setObjectName(QStringLiteral("lblWinInfo"));
        lblWinInfo->setGeometry(QRect(10, 20, 411, 51));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lblWinInfo->sizePolicy().hasHeightForWidth());
        lblWinInfo->setSizePolicy(sizePolicy);
        line = new QFrame(playerControls);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 70, 431, 20));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox = new QGroupBox(playerControls);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 90, 411, 141));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        txtSendGUIMsg = new QLineEdit(groupBox);
        txtSendGUIMsg->setObjectName(QStringLiteral("txtSendGUIMsg"));
        txtSendGUIMsg->setGeometry(QRect(10, 20, 271, 21));
        sizePolicy.setHeightForWidth(txtSendGUIMsg->sizePolicy().hasHeightForWidth());
        txtSendGUIMsg->setSizePolicy(sizePolicy);
        btnSendGUIMsg = new QPushButton(groupBox);
        btnSendGUIMsg->setObjectName(QStringLiteral("btnSendGUIMsg"));
        btnSendGUIMsg->setGeometry(QRect(290, 20, 111, 23));
        sizePolicy.setHeightForWidth(btnSendGUIMsg->sizePolicy().hasHeightForWidth());
        btnSendGUIMsg->setSizePolicy(sizePolicy);
        cmbMapSelect = new QComboBox(groupBox);
        cmbMapSelect->setObjectName(QStringLiteral("cmbMapSelect"));
        cmbMapSelect->setGeometry(QRect(10, 50, 271, 22));
        sizePolicy.setHeightForWidth(cmbMapSelect->sizePolicy().hasHeightForWidth());
        cmbMapSelect->setSizePolicy(sizePolicy);
        btnMapTP = new QPushButton(groupBox);
        btnMapTP->setObjectName(QStringLiteral("btnMapTP"));
        btnMapTP->setGeometry(QRect(290, 50, 111, 23));
        sizePolicy.setHeightForWidth(btnMapTP->sizePolicy().hasHeightForWidth());
        btnMapTP->setSizePolicy(sizePolicy);
        txtTpPlayerID1 = new QLineEdit(groupBox);
        txtTpPlayerID1->setObjectName(QStringLiteral("txtTpPlayerID1"));
        txtTpPlayerID1->setGeometry(QRect(10, 80, 131, 20));
        sizePolicy.setHeightForWidth(txtTpPlayerID1->sizePolicy().hasHeightForWidth());
        txtTpPlayerID1->setSizePolicy(sizePolicy);
        txtTpPlayerID2 = new QLineEdit(groupBox);
        txtTpPlayerID2->setObjectName(QStringLiteral("txtTpPlayerID2"));
        txtTpPlayerID2->setGeometry(QRect(152, 80, 131, 20));
        sizePolicy.setHeightForWidth(txtTpPlayerID2->sizePolicy().hasHeightForWidth());
        txtTpPlayerID2->setSizePolicy(sizePolicy);
        btnTpPlayerByID = new QPushButton(groupBox);
        btnTpPlayerByID->setObjectName(QStringLiteral("btnTpPlayerByID"));
        btnTpPlayerByID->setGeometry(QRect(290, 80, 111, 23));
        sizePolicy.setHeightForWidth(btnTpPlayerByID->sizePolicy().hasHeightForWidth());
        btnTpPlayerByID->setSizePolicy(sizePolicy);
        txtTpPlayerX = new QLineEdit(groupBox);
        txtTpPlayerX->setObjectName(QStringLiteral("txtTpPlayerX"));
        txtTpPlayerX->setGeometry(QRect(10, 110, 81, 20));
        sizePolicy.setHeightForWidth(txtTpPlayerX->sizePolicy().hasHeightForWidth());
        txtTpPlayerX->setSizePolicy(sizePolicy);
        txtTpPlayerZ = new QLineEdit(groupBox);
        txtTpPlayerZ->setObjectName(QStringLiteral("txtTpPlayerZ"));
        txtTpPlayerZ->setGeometry(QRect(200, 110, 81, 20));
        sizePolicy.setHeightForWidth(txtTpPlayerZ->sizePolicy().hasHeightForWidth());
        txtTpPlayerZ->setSizePolicy(sizePolicy);
        txtTpPlayerY = new QLineEdit(groupBox);
        txtTpPlayerY->setObjectName(QStringLiteral("txtTpPlayerY"));
        txtTpPlayerY->setGeometry(QRect(100, 110, 91, 20));
        sizePolicy.setHeightForWidth(txtTpPlayerY->sizePolicy().hasHeightForWidth());
        txtTpPlayerY->setSizePolicy(sizePolicy);
        btnTpPlayerByCoord = new QPushButton(groupBox);
        btnTpPlayerByCoord->setObjectName(QStringLiteral("btnTpPlayerByCoord"));
        btnTpPlayerByCoord->setGeometry(QRect(290, 110, 111, 23));
        sizePolicy.setHeightForWidth(btnTpPlayerByCoord->sizePolicy().hasHeightForWidth());
        btnTpPlayerByCoord->setSizePolicy(sizePolicy);
        groupBox_2 = new QGroupBox(playerControls);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 360, 411, 161));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        txtKickPlayerMsg = new QLineEdit(groupBox_2);
        txtKickPlayerMsg->setObjectName(QStringLiteral("txtKickPlayerMsg"));
        txtKickPlayerMsg->setGeometry(QRect(10, 20, 271, 20));
        sizePolicy.setHeightForWidth(txtKickPlayerMsg->sizePolicy().hasHeightForWidth());
        txtKickPlayerMsg->setSizePolicy(sizePolicy);
        btnKickPlayer = new QPushButton(groupBox_2);
        btnKickPlayer->setObjectName(QStringLiteral("btnKickPlayer"));
        btnKickPlayer->setGeometry(QRect(290, 20, 111, 23));
        sizePolicy.setHeightForWidth(btnKickPlayer->sizePolicy().hasHeightForWidth());
        btnKickPlayer->setSizePolicy(sizePolicy);
        txtBanPlayerMsg = new QLineEdit(groupBox_2);
        txtBanPlayerMsg->setObjectName(QStringLiteral("txtBanPlayerMsg"));
        txtBanPlayerMsg->setEnabled(false);
        txtBanPlayerMsg->setGeometry(QRect(10, 50, 271, 20));
        sizePolicy.setHeightForWidth(txtBanPlayerMsg->sizePolicy().hasHeightForWidth());
        txtBanPlayerMsg->setSizePolicy(sizePolicy);
        btnBanPlayer = new QPushButton(groupBox_2);
        btnBanPlayer->setObjectName(QStringLiteral("btnBanPlayer"));
        btnBanPlayer->setEnabled(false);
        btnBanPlayer->setGeometry(QRect(290, 50, 111, 23));
        sizePolicy.setHeightForWidth(btnBanPlayer->sizePolicy().hasHeightForWidth());
        btnBanPlayer->setSizePolicy(sizePolicy);
        btnPromoteToMod = new QPushButton(groupBox_2);
        btnPromoteToMod->setObjectName(QStringLiteral("btnPromoteToMod"));
        btnPromoteToMod->setEnabled(false);
        btnPromoteToMod->setGeometry(QRect(10, 100, 191, 23));
        sizePolicy.setHeightForWidth(btnPromoteToMod->sizePolicy().hasHeightForWidth());
        btnPromoteToMod->setSizePolicy(sizePolicy);
        btnDemoteToPlayer = new QPushButton(groupBox_2);
        btnDemoteToPlayer->setObjectName(QStringLiteral("btnDemoteToPlayer"));
        btnDemoteToPlayer->setEnabled(false);
        btnDemoteToPlayer->setGeometry(QRect(210, 100, 191, 23));
        sizePolicy.setHeightForWidth(btnDemoteToPlayer->sizePolicy().hasHeightForWidth());
        btnDemoteToPlayer->setSizePolicy(sizePolicy);
        line_2 = new QFrame(groupBox_2);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 80, 411, 16));
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        btnMutePlayer = new QPushButton(groupBox_2);
        btnMutePlayer->setObjectName(QStringLiteral("btnMutePlayer"));
        btnMutePlayer->setEnabled(false);
        btnMutePlayer->setGeometry(QRect(10, 130, 191, 23));
        sizePolicy.setHeightForWidth(btnMutePlayer->sizePolicy().hasHeightForWidth());
        btnMutePlayer->setSizePolicy(sizePolicy);
        btnUnmutePlayer = new QPushButton(groupBox_2);
        btnUnmutePlayer->setObjectName(QStringLiteral("btnUnmutePlayer"));
        btnUnmutePlayer->setEnabled(false);
        btnUnmutePlayer->setGeometry(QRect(210, 130, 191, 23));
        sizePolicy.setHeightForWidth(btnUnmutePlayer->sizePolicy().hasHeightForWidth());
        btnUnmutePlayer->setSizePolicy(sizePolicy);
        groupBox_3 = new QGroupBox(playerControls);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 530, 411, 81));
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        btnGetPlayerPos = new QPushButton(groupBox_3);
        btnGetPlayerPos->setObjectName(QStringLiteral("btnGetPlayerPos"));
        btnGetPlayerPos->setGeometry(QRect(10, 20, 121, 23));
        sizePolicy.setHeightForWidth(btnGetPlayerPos->sizePolicy().hasHeightForWidth());
        btnGetPlayerPos->setSizePolicy(sizePolicy);
        btnGetPlayerRot = new QPushButton(groupBox_3);
        btnGetPlayerRot->setObjectName(QStringLiteral("btnGetPlayerRot"));
        btnGetPlayerRot->setGeometry(QRect(280, 20, 121, 23));
        sizePolicy.setHeightForWidth(btnGetPlayerRot->sizePolicy().hasHeightForWidth());
        btnGetPlayerRot->setSizePolicy(sizePolicy);
        btnGetPlayerPonyData = new QPushButton(groupBox_3);
        btnGetPlayerPonyData->setObjectName(QStringLiteral("btnGetPlayerPonyData"));
        btnGetPlayerPonyData->setGeometry(QRect(140, 20, 131, 23));
        sizePolicy.setHeightForWidth(btnGetPlayerPonyData->sizePolicy().hasHeightForWidth());
        btnGetPlayerPonyData->setSizePolicy(sizePolicy);
        txtPlayerInfoResult = new QLineEdit(groupBox_3);
        txtPlayerInfoResult->setObjectName(QStringLiteral("txtPlayerInfoResult"));
        txtPlayerInfoResult->setGeometry(QRect(10, 50, 391, 20));
        sizePolicy.setHeightForWidth(txtPlayerInfoResult->sizePolicy().hasHeightForWidth());
        txtPlayerInfoResult->setSizePolicy(sizePolicy);
        line_3 = new QFrame(playerControls);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(0, 0, 431, 20));
        sizePolicy.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        groupBox_4 = new QGroupBox(playerControls);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 240, 411, 111));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        txtAnnouncementMsg = new QLineEdit(groupBox_4);
        txtAnnouncementMsg->setObjectName(QStringLiteral("txtAnnouncementMsg"));
        txtAnnouncementMsg->setGeometry(QRect(130, 20, 271, 20));
        sizePolicy.setHeightForWidth(txtAnnouncementMsg->sizePolicy().hasHeightForWidth());
        txtAnnouncementMsg->setSizePolicy(sizePolicy);
        lblAnnouncementMsg = new QLabel(groupBox_4);
        lblAnnouncementMsg->setObjectName(QStringLiteral("lblAnnouncementMsg"));
        lblAnnouncementMsg->setGeometry(QRect(10, 20, 101, 21));
        sizePolicy.setHeightForWidth(lblAnnouncementMsg->sizePolicy().hasHeightForWidth());
        lblAnnouncementMsg->setSizePolicy(sizePolicy);
        lblAnnoucementMsgLenght = new QLabel(groupBox_4);
        lblAnnoucementMsgLenght->setObjectName(QStringLiteral("lblAnnoucementMsgLenght"));
        lblAnnoucementMsgLenght->setGeometry(QRect(10, 50, 111, 20));
        sizePolicy.setHeightForWidth(lblAnnoucementMsgLenght->sizePolicy().hasHeightForWidth());
        lblAnnoucementMsgLenght->setSizePolicy(sizePolicy);
        spbAnnoucementLenght = new QDoubleSpinBox(groupBox_4);
        spbAnnoucementLenght->setObjectName(QStringLiteral("spbAnnoucementLenght"));
        spbAnnoucementLenght->setGeometry(QRect(130, 50, 271, 22));
        sizePolicy.setHeightForWidth(spbAnnoucementLenght->sizePolicy().hasHeightForWidth());
        spbAnnoucementLenght->setSizePolicy(sizePolicy);
        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 80, 191, 23));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        btnSendAnnouncement = new QPushButton(groupBox_4);
        btnSendAnnouncement->setObjectName(QStringLiteral("btnSendAnnouncement"));
        btnSendAnnouncement->setGeometry(QRect(210, 80, 191, 23));
        sizePolicy.setHeightForWidth(btnSendAnnouncement->sizePolicy().hasHeightForWidth());
        btnSendAnnouncement->setSizePolicy(sizePolicy);

        retranslateUi(playerControls);

        QMetaObject::connectSlotsByName(playerControls);
    } // setupUi

    void retranslateUi(QWidget *playerControls)
    {
        playerControls->setWindowTitle(QApplication::translate("playerControls", "Player Controls", 0));
        lblWinInfo->setText(QApplication::translate("playerControls", "<html><head/><body><p align=\"center\">You must set a player first to use any of these controls.</p><p align=\"center\">Set a Player by clicking on a player on the Player List.</p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("playerControls", "General", 0));
        btnSendGUIMsg->setText(QApplication::translate("playerControls", "Send GUI Message", 0));
        cmbMapSelect->clear();
        cmbMapSelect->insertItems(0, QStringList()
         << QApplication::translate("playerControls", "Map Select...", 0)
         << QApplication::translate("playerControls", "ponyville", 0)
         << QApplication::translate("playerControls", "canterlot", 0)
         << QApplication::translate("playerControls", "cloudsdale", 0)
         << QApplication::translate("playerControls", "sweetappleacres", 0)
         << QApplication::translate("playerControls", "gemmines", 0)
         << QApplication::translate("playerControls", "ponyville library 1st floor", 0)
         << QApplication::translate("playerControls", "ponyville library 2nd floor", 0)
         << QApplication::translate("playerControls", "sugarcubecorner", 0)
         << QApplication::translate("playerControls", "raritysboutique", 0)
         << QApplication::translate("playerControls", "everfree3", 0)
         << QApplication::translate("playerControls", "zecoras", 0)
         << QApplication::translate("playerControls", "everfree1", 0)
         << QApplication::translate("playerControls", "appaloosa", 0)
         << QApplication::translate("playerControls", "cottage", 0)
         << QApplication::translate("playerControls", "tm01", 0)
        );
        btnMapTP->setText(QApplication::translate("playerControls", "Map Teleport", 0));
        btnTpPlayerByID->setText(QApplication::translate("playerControls", "Player Teleport", 0));
        btnTpPlayerByCoord->setText(QApplication::translate("playerControls", "Pos. Teleport", 0));
        groupBox_2->setTitle(QApplication::translate("playerControls", "Moderation", 0));
        btnKickPlayer->setText(QApplication::translate("playerControls", "Kick Player", 0));
        txtBanPlayerMsg->setText(QApplication::translate("playerControls", "Coming Soon", 0));
        btnBanPlayer->setText(QApplication::translate("playerControls", "Ban Player", 0));
        btnPromoteToMod->setText(QApplication::translate("playerControls", "Promote To Moderator (Coming Soon)", 0));
        btnDemoteToPlayer->setText(QApplication::translate("playerControls", "Demote To Player (Coming Soon)", 0));
        btnMutePlayer->setText(QApplication::translate("playerControls", "Mute Player (Coming Soon)", 0));
        btnUnmutePlayer->setText(QApplication::translate("playerControls", "UnMute Player (Coming Soon)", 0));
        groupBox_3->setTitle(QApplication::translate("playerControls", "Get Player Information", 0));
        btnGetPlayerPos->setText(QApplication::translate("playerControls", "Get Position", 0));
        btnGetPlayerRot->setText(QApplication::translate("playerControls", "Get Rotation", 0));
        btnGetPlayerPonyData->setText(QApplication::translate("playerControls", "Get ponyData", 0));
        groupBox_4->setTitle(QApplication::translate("playerControls", "Announcement Controls", 0));
        lblAnnouncementMsg->setText(QApplication::translate("playerControls", "Message", 0));
        lblAnnoucementMsgLenght->setText(QApplication::translate("playerControls", "Show Time Lenght", 0));
        spbAnnoucementLenght->setSuffix(QApplication::translate("playerControls", "s", 0));
        pushButton->setText(QApplication::translate("playerControls", "Send Announcement to Everyone", 0));
        btnSendAnnouncement->setText(QApplication::translate("playerControls", "Send Announcement to Set Player", 0));
    } // retranslateUi

};

namespace Ui {
    class playerControls: public Ui_playerControls {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERCONTROLS_H
