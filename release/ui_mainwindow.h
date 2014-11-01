/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave_Log;
    QAction *actionExit;
    QAction *actionStart_Server;
    QAction *actionRestart_Server;
    QAction *actionStop_Server;
    QAction *actionServer_Settings;
    QAction *actionSettings;
    QAction *actionPlugins;
    QAction *actionQuest_Script_Tutorial;
    QAction *actionPonyforums_net_Post;
    QAction *actionAbout_LoEWCT;
    QAction *action_LoEWCT_Client_Luncher_Settings;
    QWidget *centralWidget;
    QTabWidget *mainConsole;
    QWidget *tabConsole;
    QPlainTextEdit *consoleLog;
    QLineEdit *cmdLine;
    QPushButton *sendCmdLine;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSaveServerLog;
    QPushButton *btnCopyClipboard;
    QPushButton *btnClearConsoleLog;
    QWidget *tabChat;
    QTabWidget *logChat;
    QWidget *tabGlobalChat;
    QLineEdit *chatLine_Global;
    QPushButton *sendChatLine_Global;
    QPlainTextEdit *logChatGlobal;
    QWidget *tabLocalChat;
    QLineEdit *chatLine_Local;
    QPushButton *sendChatLine_Local;
    QPlainTextEdit *logChatLocal;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *lblSelScene_localChat;
    QComboBox *comboBox;
    QWidget *tabPartyChat;
    QLabel *label_2;
    QWidget *tabHerdChat;
    QLabel *label_3;
    QWidget *tabWhisperChat;
    QPlainTextEdit *logChatWhisper;
    QLineEdit *chatLine_Whisper;
    QPushButton *sendChatLine_Whisper;
    QLabel *lblWhisperChatInfo;
    QTabWidget *playerListWidget;
    QWidget *tabPlayersList;
    QListView *playerList;
    QGroupBox *boxServerControls;
    QFrame *line;
    QLabel *lblLogInServer;
    QLabel *lblGameServer;
    QLabel *lbPlayersOnline;
    QLabel *lblLogInServerStatus;
    QLabel *lblGameServerStatus;
    QLabel *lblPlayersConnected;
    QPushButton *btnPlayerControls;
    QFrame *line_2;
    QPushButton *btnMovieMakerTools;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QPushButton *btnStartServer;
    QPushButton *btnStopServer;
    QPushButton *btnRestartServer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuServer;
    QMenu *menu_LoEWCT;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(818, 678);
        MainWindow->setMinimumSize(QSize(818, 678));
        MainWindow->setMaximumSize(QSize(818, 678));
        actionSave_Log = new QAction(MainWindow);
        actionSave_Log->setObjectName(QStringLiteral("actionSave_Log"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/icons/drive_disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Log->setIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionStart_Server = new QAction(MainWindow);
        actionStart_Server->setObjectName(QStringLiteral("actionStart_Server"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/icons/server_go.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart_Server->setIcon(icon1);
        actionRestart_Server = new QAction(MainWindow);
        actionRestart_Server->setObjectName(QStringLiteral("actionRestart_Server"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/icons/arrow_refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRestart_Server->setIcon(icon2);
        actionStop_Server = new QAction(MainWindow);
        actionStop_Server->setObjectName(QStringLiteral("actionStop_Server"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/icons/server_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop_Server->setIcon(icon3);
        actionServer_Settings = new QAction(MainWindow);
        actionServer_Settings->setObjectName(QStringLiteral("actionServer_Settings"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/icons/server_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionServer_Settings->setIcon(icon4);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/icons/application_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSettings->setIcon(icon5);
        actionPlugins = new QAction(MainWindow);
        actionPlugins->setObjectName(QStringLiteral("actionPlugins"));
        actionQuest_Script_Tutorial = new QAction(MainWindow);
        actionQuest_Script_Tutorial->setObjectName(QStringLiteral("actionQuest_Script_Tutorial"));
        actionPonyforums_net_Post = new QAction(MainWindow);
        actionPonyforums_net_Post->setObjectName(QStringLiteral("actionPonyforums_net_Post"));
        actionAbout_LoEWCT = new QAction(MainWindow);
        actionAbout_LoEWCT->setObjectName(QStringLiteral("actionAbout_LoEWCT"));
        action_LoEWCT_Client_Luncher_Settings = new QAction(MainWindow);
        action_LoEWCT_Client_Luncher_Settings->setObjectName(QStringLiteral("action_LoEWCT_Client_Luncher_Settings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mainConsole = new QTabWidget(centralWidget);
        mainConsole->setObjectName(QStringLiteral("mainConsole"));
        mainConsole->setGeometry(QRect(10, 10, 556, 491));
        mainConsole->setTabPosition(QTabWidget::North);
        tabConsole = new QWidget();
        tabConsole->setObjectName(QStringLiteral("tabConsole"));
        consoleLog = new QPlainTextEdit(tabConsole);
        consoleLog->setObjectName(QStringLiteral("consoleLog"));
        consoleLog->setGeometry(QRect(10, 10, 531, 381));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        QBrush brush4(QColor(10, 36, 106, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        consoleLog->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Lucida Console"));
        font.setBold(true);
        font.setWeight(75);
        consoleLog->setFont(font);
        consoleLog->setReadOnly(true);
        cmdLine = new QLineEdit(tabConsole);
        cmdLine->setObjectName(QStringLiteral("cmdLine"));
        cmdLine->setGeometry(QRect(10, 400, 441, 20));
        sendCmdLine = new QPushButton(tabConsole);
        sendCmdLine->setObjectName(QStringLiteral("sendCmdLine"));
        sendCmdLine->setGeometry(QRect(460, 400, 81, 23));
        layoutWidget = new QWidget(tabConsole);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 430, 531, 28));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnSaveServerLog = new QPushButton(layoutWidget);
        btnSaveServerLog->setObjectName(QStringLiteral("btnSaveServerLog"));
        btnSaveServerLog->setIcon(icon);

        horizontalLayout_2->addWidget(btnSaveServerLog);

        btnCopyClipboard = new QPushButton(layoutWidget);
        btnCopyClipboard->setObjectName(QStringLiteral("btnCopyClipboard"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/icons/page_white_paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCopyClipboard->setIcon(icon6);

        horizontalLayout_2->addWidget(btnCopyClipboard);

        btnClearConsoleLog = new QPushButton(layoutWidget);
        btnClearConsoleLog->setObjectName(QStringLiteral("btnClearConsoleLog"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/icons/bin_empty.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClearConsoleLog->setIcon(icon7);

        horizontalLayout_2->addWidget(btnClearConsoleLog);

        mainConsole->addTab(tabConsole, QString());
        tabChat = new QWidget();
        tabChat->setObjectName(QStringLiteral("tabChat"));
        logChat = new QTabWidget(tabChat);
        logChat->setObjectName(QStringLiteral("logChat"));
        logChat->setGeometry(QRect(10, 10, 531, 451));
        tabGlobalChat = new QWidget();
        tabGlobalChat->setObjectName(QStringLiteral("tabGlobalChat"));
        chatLine_Global = new QLineEdit(tabGlobalChat);
        chatLine_Global->setObjectName(QStringLiteral("chatLine_Global"));
        chatLine_Global->setGeometry(QRect(9, 400, 421, 20));
        sendChatLine_Global = new QPushButton(tabGlobalChat);
        sendChatLine_Global->setObjectName(QStringLiteral("sendChatLine_Global"));
        sendChatLine_Global->setGeometry(QRect(440, 400, 75, 23));
        logChatGlobal = new QPlainTextEdit(tabGlobalChat);
        logChatGlobal->setObjectName(QStringLiteral("logChatGlobal"));
        logChatGlobal->setGeometry(QRect(10, 10, 511, 381));
        logChatGlobal->setReadOnly(true);
        logChat->addTab(tabGlobalChat, QString());
        tabLocalChat = new QWidget();
        tabLocalChat->setObjectName(QStringLiteral("tabLocalChat"));
        chatLine_Local = new QLineEdit(tabLocalChat);
        chatLine_Local->setObjectName(QStringLiteral("chatLine_Local"));
        chatLine_Local->setGeometry(QRect(10, 400, 421, 20));
        sendChatLine_Local = new QPushButton(tabLocalChat);
        sendChatLine_Local->setObjectName(QStringLiteral("sendChatLine_Local"));
        sendChatLine_Local->setGeometry(QRect(440, 400, 75, 23));
        logChatLocal = new QPlainTextEdit(tabLocalChat);
        logChatLocal->setObjectName(QStringLiteral("logChatLocal"));
        logChatLocal->setGeometry(QRect(10, 40, 511, 351));
        logChatLocal->setReadOnly(true);
        layoutWidget1 = new QWidget(tabLocalChat);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 511, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lblSelScene_localChat = new QLabel(layoutWidget1);
        lblSelScene_localChat->setObjectName(QStringLiteral("lblSelScene_localChat"));

        horizontalLayout->addWidget(lblSelScene_localChat);

        comboBox = new QComboBox(layoutWidget1);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        logChat->addTab(tabLocalChat, QString());
        tabPartyChat = new QWidget();
        tabPartyChat->setObjectName(QStringLiteral("tabPartyChat"));
        label_2 = new QLabel(tabPartyChat);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(15, 10, 501, 401));
        logChat->addTab(tabPartyChat, QString());
        tabHerdChat = new QWidget();
        tabHerdChat->setObjectName(QStringLiteral("tabHerdChat"));
        label_3 = new QLabel(tabHerdChat);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 501, 401));
        label_3->setAlignment(Qt::AlignCenter);
        logChat->addTab(tabHerdChat, QString());
        tabWhisperChat = new QWidget();
        tabWhisperChat->setObjectName(QStringLiteral("tabWhisperChat"));
        logChatWhisper = new QPlainTextEdit(tabWhisperChat);
        logChatWhisper->setObjectName(QStringLiteral("logChatWhisper"));
        logChatWhisper->setGeometry(QRect(10, 40, 511, 351));
        logChatWhisper->setReadOnly(true);
        chatLine_Whisper = new QLineEdit(tabWhisperChat);
        chatLine_Whisper->setObjectName(QStringLiteral("chatLine_Whisper"));
        chatLine_Whisper->setGeometry(QRect(10, 400, 421, 20));
        sendChatLine_Whisper = new QPushButton(tabWhisperChat);
        sendChatLine_Whisper->setObjectName(QStringLiteral("sendChatLine_Whisper"));
        sendChatLine_Whisper->setGeometry(QRect(440, 400, 75, 23));
        lblWhisperChatInfo = new QLabel(tabWhisperChat);
        lblWhisperChatInfo->setObjectName(QStringLiteral("lblWhisperChatInfo"));
        lblWhisperChatInfo->setGeometry(QRect(15, 10, 501, 20));
        lblWhisperChatInfo->setAlignment(Qt::AlignCenter);
        logChat->addTab(tabWhisperChat, QString());
        mainConsole->addTab(tabChat, QString());
        playerListWidget = new QTabWidget(centralWidget);
        playerListWidget->setObjectName(QStringLiteral("playerListWidget"));
        playerListWidget->setGeometry(QRect(580, 10, 226, 491));
        tabPlayersList = new QWidget();
        tabPlayersList->setObjectName(QStringLiteral("tabPlayersList"));
        playerList = new QListView(tabPlayersList);
        playerList->setObjectName(QStringLiteral("playerList"));
        playerList->setGeometry(QRect(10, 10, 201, 445));
        playerListWidget->addTab(tabPlayersList, QString());
        boxServerControls = new QGroupBox(centralWidget);
        boxServerControls->setObjectName(QStringLiteral("boxServerControls"));
        boxServerControls->setGeometry(QRect(10, 510, 791, 121));
        boxServerControls->setAlignment(Qt::AlignCenter);
        line = new QFrame(boxServerControls);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(260, 20, 20, 91));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        lblLogInServer = new QLabel(boxServerControls);
        lblLogInServer->setObjectName(QStringLiteral("lblLogInServer"));
        lblLogInServer->setGeometry(QRect(280, 20, 201, 21));
        lblLogInServer->setScaledContents(false);
        lblLogInServer->setWordWrap(false);
        lblLogInServer->setOpenExternalLinks(false);
        lblGameServer = new QLabel(boxServerControls);
        lblGameServer->setObjectName(QStringLiteral("lblGameServer"));
        lblGameServer->setGeometry(QRect(280, 50, 201, 21));
        lbPlayersOnline = new QLabel(boxServerControls);
        lbPlayersOnline->setObjectName(QStringLiteral("lbPlayersOnline"));
        lbPlayersOnline->setGeometry(QRect(280, 80, 201, 21));
        lblLogInServerStatus = new QLabel(boxServerControls);
        lblLogInServerStatus->setObjectName(QStringLiteral("lblLogInServerStatus"));
        lblLogInServerStatus->setGeometry(QRect(430, 20, 81, 21));
        lblLogInServerStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblGameServerStatus = new QLabel(boxServerControls);
        lblGameServerStatus->setObjectName(QStringLiteral("lblGameServerStatus"));
        lblGameServerStatus->setGeometry(QRect(430, 50, 81, 21));
        lblGameServerStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lblPlayersConnected = new QLabel(boxServerControls);
        lblPlayersConnected->setObjectName(QStringLiteral("lblPlayersConnected"));
        lblPlayersConnected->setGeometry(QRect(430, 80, 81, 21));
        lblPlayersConnected->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnPlayerControls = new QPushButton(boxServerControls);
        btnPlayerControls->setObjectName(QStringLiteral("btnPlayerControls"));
        btnPlayerControls->setGeometry(QRect(530, 20, 251, 41));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/icons/user_edit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlayerControls->setIcon(icon8);
        line_2 = new QFrame(boxServerControls);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(510, 20, 20, 91));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        btnMovieMakerTools = new QPushButton(boxServerControls);
        btnMovieMakerTools->setObjectName(QStringLiteral("btnMovieMakerTools"));
        btnMovieMakerTools->setGeometry(QRect(530, 70, 251, 41));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/icons/film.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMovieMakerTools->setIcon(icon9);
        layoutWidget2 = new QWidget(boxServerControls);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 20, 251, 92));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnStartServer = new QPushButton(layoutWidget2);
        btnStartServer->setObjectName(QStringLiteral("btnStartServer"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/icons/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStartServer->setIcon(icon10);

        verticalLayout->addWidget(btnStartServer);

        btnStopServer = new QPushButton(layoutWidget2);
        btnStopServer->setObjectName(QStringLiteral("btnStopServer"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/icons/controller.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStopServer->setIcon(icon11);

        verticalLayout->addWidget(btnStopServer);

        btnRestartServer = new QPushButton(layoutWidget2);
        btnRestartServer->setObjectName(QStringLiteral("btnRestartServer"));
        btnRestartServer->setIcon(icon2);

        verticalLayout->addWidget(btnRestartServer);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 818, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuServer = new QMenu(menuBar);
        menuServer->setObjectName(QStringLiteral("menuServer"));
        menu_LoEWCT = new QMenu(menuBar);
        menu_LoEWCT->setObjectName(QStringLiteral("menu_LoEWCT"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuServer->menuAction());
        menuBar->addAction(menu_LoEWCT->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSave_Log);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuServer->addAction(actionStart_Server);
        menuServer->addAction(actionRestart_Server);
        menuServer->addAction(actionStop_Server);
        menuServer->addSeparator();
        menuServer->addAction(actionServer_Settings);
        menu_LoEWCT->addAction(actionPlugins);
        menu_LoEWCT->addSeparator();
        menu_LoEWCT->addAction(actionSettings);
        menu_LoEWCT->addAction(action_LoEWCT_Client_Luncher_Settings);
        menuHelp->addAction(actionQuest_Script_Tutorial);
        menuHelp->addAction(actionPonyforums_net_Post);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout_LoEWCT);

        retranslateUi(MainWindow);
        QObject::connect(cmdLine, SIGNAL(returnPressed()), sendCmdLine, SLOT(click()));

        mainConsole->setCurrentIndex(0);
        logChat->setCurrentIndex(0);
        playerListWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "[LoEWCT] Control Panel v1.0", 0));
        actionSave_Log->setText(QApplication::translate("MainWindow", "Save Log...", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionStart_Server->setText(QApplication::translate("MainWindow", "Start Server", 0));
        actionRestart_Server->setText(QApplication::translate("MainWindow", "Restart Server", 0));
        actionStop_Server->setText(QApplication::translate("MainWindow", "Stop Server", 0));
        actionServer_Settings->setText(QApplication::translate("MainWindow", "Server Settings", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "[LoEWCT] Settings", 0));
        actionPlugins->setText(QApplication::translate("MainWindow", "Plugins", 0));
        actionQuest_Script_Tutorial->setText(QApplication::translate("MainWindow", "Quest Script Tutorial", 0));
        actionPonyforums_net_Post->setText(QApplication::translate("MainWindow", "ponyforums.net Post", 0));
        actionAbout_LoEWCT->setText(QApplication::translate("MainWindow", "About [LoEWCT]...", 0));
        action_LoEWCT_Client_Luncher_Settings->setText(QApplication::translate("MainWindow", "[LoEWCT] Client Luncher Settings", 0));
        consoleLog->setPlainText(QString());
        sendCmdLine->setText(QApplication::translate("MainWindow", "Send", 0));
        btnSaveServerLog->setText(QApplication::translate("MainWindow", "Save Log", 0));
        btnCopyClipboard->setText(QApplication::translate("MainWindow", "Copy to Clipboard", 0));
        btnClearConsoleLog->setText(QApplication::translate("MainWindow", "Clear Log", 0));
        mainConsole->setTabText(mainConsole->indexOf(tabConsole), QApplication::translate("MainWindow", "Server Console", 0));
        sendChatLine_Global->setText(QApplication::translate("MainWindow", "Send", 0));
        logChat->setTabText(logChat->indexOf(tabGlobalChat), QApplication::translate("MainWindow", "Global", 0));
        sendChatLine_Local->setText(QApplication::translate("MainWindow", "Send", 0));
        lblSelScene_localChat->setText(QApplication::translate("MainWindow", "Select Scene", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ponyville", 0)
         << QApplication::translate("MainWindow", "canterlot", 0)
         << QApplication::translate("MainWindow", "cloudsdale", 0)
        );
        logChat->setTabText(logChat->indexOf(tabLocalChat), QApplication::translate("MainWindow", "Local", 0));
        label_2->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Party Chat is not available at the moment.</span></p></body></html>", 0));
        logChat->setTabText(logChat->indexOf(tabPartyChat), QApplication::translate("MainWindow", "Party", 0));
        label_3->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:16pt; font-weight:600;\">Herd Chat is not available at the moment.</span></p></body></html>", 0));
        logChat->setTabText(logChat->indexOf(tabHerdChat), QApplication::translate("MainWindow", "Herd", 0));
        sendChatLine_Whisper->setText(QApplication::translate("MainWindow", "Send", 0));
        lblWhisperChatInfo->setText(QApplication::translate("MainWindow", "People will know you as <SERVER> | You MUST Set a Player to use this chat.", 0));
        logChat->setTabText(logChat->indexOf(tabWhisperChat), QApplication::translate("MainWindow", "Whisper", 0));
        mainConsole->setTabText(mainConsole->indexOf(tabChat), QApplication::translate("MainWindow", "Chat", 0));
        playerListWidget->setTabText(playerListWidget->indexOf(tabPlayersList), QApplication::translate("MainWindow", "Player List", 0));
        boxServerControls->setTitle(QApplication::translate("MainWindow", "Server Status and Controls", 0));
        lblLogInServer->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Log In Server</span></p></body></html>", 0));
        lblGameServer->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Game Server</span></p></body></html>", 0));
        lbPlayersOnline->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">Players Connected</span></p></body></html>", 0));
        lblLogInServerStatus->setText(QApplication::translate("MainWindow", "OFFLINE", 0));
        lblGameServerStatus->setText(QApplication::translate("MainWindow", "OFFLINE", 0));
        lblPlayersConnected->setText(QApplication::translate("MainWindow", "? / ?", 0));
        btnPlayerControls->setText(QApplication::translate("MainWindow", "Player Controls", 0));
        btnMovieMakerTools->setText(QApplication::translate("MainWindow", "LoE Movie Making Tools", 0));
        btnStartServer->setText(QApplication::translate("MainWindow", "Start Log In Server", 0));
        btnStopServer->setText(QApplication::translate("MainWindow", "Start Game Server", 0));
        btnRestartServer->setText(QApplication::translate("MainWindow", "Restart Game Server", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuServer->setTitle(QApplication::translate("MainWindow", "Server", 0));
        menu_LoEWCT->setTitle(QApplication::translate("MainWindow", "[LoEWCT]", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
