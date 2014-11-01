/********************************************************************************
** Form generated from reading UI file 'loewctSettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOEWCTSETTINGSWIDGET_H
#define UI_LOEWCTSETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loewctSettings
{
public:
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QGroupBox *groupBox;
    QLabel *label_11;
    QSpinBox *spinBox_3;
    QPushButton *pushButton_5;
    QWidget *tabSpecial;
    QGroupBox *groupBox_3;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QFrame *line_4;
    QCheckBox *checkBox_7;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QLabel *label_8;
    QLineEdit *lineEdit_5;
    QLabel *label_9;
    QLineEdit *lineEdit_6;
    QLabel *label_10;
    QWidget *tabDatabase;
    QLabel *label;
    QComboBox *comboBox;
    QFrame *line;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_7;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;
    QPushButton *pushButton;

    void setupUi(QWidget *loewctSettings)
    {
        if (loewctSettings->objectName().isEmpty())
            loewctSettings->setObjectName(QStringLiteral("loewctSettings"));
        loewctSettings->resize(640, 480);
        tabWidget = new QTabWidget(loewctSettings);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 621, 431));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QStringLiteral("tabGeneral"));
        groupBox = new QGroupBox(tabGeneral);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 601, 80));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 20, 281, 21));
        spinBox_3 = new QSpinBox(groupBox);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setGeometry(QRect(300, 20, 211, 22));
        spinBox_3->setMaximum(99999999);
        spinBox_3->setValue(5000);
        pushButton_5 = new QPushButton(groupBox);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(520, 20, 71, 23));
        tabWidget->addTab(tabGeneral, QString());
        tabSpecial = new QWidget();
        tabSpecial->setObjectName(QStringLiteral("tabSpecial"));
        groupBox_3 = new QGroupBox(tabSpecial);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 591, 201));
        checkBox_5 = new QCheckBox(groupBox_3);
        checkBox_5->setObjectName(QStringLiteral("checkBox_5"));
        checkBox_5->setGeometry(QRect(10, 20, 261, 17));
        checkBox_6 = new QCheckBox(groupBox_3);
        checkBox_6->setObjectName(QStringLiteral("checkBox_6"));
        checkBox_6->setGeometry(QRect(280, 20, 301, 17));
        line_4 = new QFrame(groupBox_3);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(0, 70, 591, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        checkBox_7 = new QCheckBox(groupBox_3);
        checkBox_7->setObjectName(QStringLiteral("checkBox_7"));
        checkBox_7->setEnabled(false);
        checkBox_7->setGeometry(QRect(10, 50, 571, 17));
        formLayoutWidget_2 = new QWidget(groupBox_3);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(10, 110, 571, 81));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setHorizontalSpacing(136);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(formLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        lineEdit_4 = new QLineEdit(formLayoutWidget_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, lineEdit_4);

        label_8 = new QLabel(formLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_8);

        lineEdit_5 = new QLineEdit(formLayoutWidget_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEdit_5);

        label_9 = new QLabel(formLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_9);

        lineEdit_6 = new QLineEdit(formLayoutWidget_2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEdit_6);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 90, 571, 16));
        label_10->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tabSpecial, QString());
        tabDatabase = new QWidget();
        tabDatabase->setObjectName(QStringLiteral("tabDatabase"));
        label = new QLabel(tabDatabase);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 321, 21));
        comboBox = new QComboBox(tabDatabase);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(288, 10, 311, 22));
        line = new QFrame(tabDatabase);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 40, 621, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox_2 = new QGroupBox(tabDatabase);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 60, 591, 141));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 271, 21));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(282, 20, 301, 20));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(282, 50, 301, 20));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 50, 271, 21));
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(282, 80, 301, 20));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 80, 271, 21));
        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(282, 110, 301, 20));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 110, 271, 21));
        tabWidget->addTab(tabDatabase, QString());
        buttonBox = new QDialogButtonBox(loewctSettings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(390, 450, 241, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        pushButton = new QPushButton(loewctSettings);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 450, 141, 23));

        retranslateUi(loewctSettings);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(loewctSettings);
    } // setupUi

    void retranslateUi(QWidget *loewctSettings)
    {
        loewctSettings->setWindowTitle(QApplication::translate("loewctSettings", "[LoEWCT] Settings", 0));
        groupBox->setTitle(QApplication::translate("loewctSettings", "Server Settings", 0));
        label_11->setText(QApplication::translate("loewctSettings", "Player List Refresh Interval", 0));
        spinBox_3->setSuffix(QApplication::translate("loewctSettings", "ms", 0));
        pushButton_5->setText(QApplication::translate("loewctSettings", "Reset", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QApplication::translate("loewctSettings", "General Settings", 0));
        groupBox_3->setTitle(QApplication::translate("loewctSettings", "Chat Messages", 0));
        checkBox_5->setText(QApplication::translate("loewctSettings", "Enable >greentext (AKA 4chan quotes)", 0));
        checkBox_6->setText(QApplication::translate("loewctSettings", "Show Player Joined/Left Messages", 0));
        checkBox_7->setText(QApplication::translate("loewctSettings", "Enable use of color codes for easy text coloring (unimplemented yet)", 0));
        label_6->setText(QApplication::translate("loewctSettings", "Server Prefix", 0));
        lineEdit_4->setText(QApplication::translate("loewctSettings", "[LoEWCT]", 0));
        label_8->setText(QApplication::translate("loewctSettings", "Message of the Day (MOTD)", 0));
        lineEdit_5->setText(QApplication::translate("loewctSettings", "Parties at SugarcaneCorner all always awesome! Why won't you come and join the fun?", 0));
        label_9->setText(QApplication::translate("loewctSettings", "Server Rules", 0));
        lineEdit_6->setText(QApplication::translate("loewctSettings", "1. No swearing excesively \\n2. No Inapropiate Role-plays or simulations \\n3. Respect Everyone \\n4. Have Fun!", 0));
        label_10->setText(QApplication::translate("loewctSettings", "You can use \"\\n\" (for new line) on the MOTD and rules", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabSpecial), QApplication::translate("loewctSettings", "Server Goodies", 0));
        label->setText(QApplication::translate("loewctSettings", "Database Service:", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("loewctSettings", "Flatfile (default)", 0)
         << QApplication::translate("loewctSettings", "MySQL", 0)
         << QApplication::translate("loewctSettings", "SQLite", 0)
        );
        groupBox_2->setTitle(QApplication::translate("loewctSettings", "MySQL Settings", 0));
        label_2->setText(QApplication::translate("loewctSettings", "Database Host Address", 0));
        label_3->setText(QApplication::translate("loewctSettings", "Database Username", 0));
        label_4->setText(QApplication::translate("loewctSettings", "Database Password", 0));
        label_5->setText(QApplication::translate("loewctSettings", "Database Name", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabDatabase), QApplication::translate("loewctSettings", "Databases", 0));
        pushButton->setText(QApplication::translate("loewctSettings", "Revert All To Defaults", 0));
    } // retranslateUi

};

namespace Ui {
    class loewctSettings: public Ui_loewctSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOEWCTSETTINGSWIDGET_H
