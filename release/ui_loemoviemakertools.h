/********************************************************************************
** Form generated from reading UI file 'loemoviemakertools.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOEMOVIEMAKERTOOLS_H
#define UI_LOEMOVIEMAKERTOOLS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loeMovieMakerTools
{
public:
    QLabel *label;
    QFrame *line;
    QGroupBox *groupBox;
    QLabel *label_2;
    QSpinBox *spinBox;
    QPushButton *pushButton;
    QGroupBox *groupBox_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QFrame *line_2;
    QLabel *label_4;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *loeMovieMakerTools)
    {
        if (loeMovieMakerTools->objectName().isEmpty())
            loeMovieMakerTools->setObjectName(QStringLiteral("loeMovieMakerTools"));
        loeMovieMakerTools->resize(310, 430);
        label = new QLabel(loeMovieMakerTools);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 291, 71));
        line = new QFrame(loeMovieMakerTools);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 80, 311, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox = new QGroupBox(loeMovieMakerTools);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 100, 291, 81));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 20, 141, 22));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setGeometry(QRect(161, 20, 121, 22));
        spinBox->setMaximum(99999);
        spinBox->setValue(6000);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 50, 271, 23));
        groupBox_2 = new QGroupBox(loeMovieMakerTools);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 190, 291, 231));
        lineEdit = new QLineEdit(groupBox_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(10, 50, 171, 20));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setGeometry(QRect(190, 50, 91, 23));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 20, 271, 16));
        label_3->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 200, 271, 23));
        line_2 = new QFrame(groupBox_2);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(0, 80, 291, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 90, 271, 71));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(10, 170, 271, 20));

        retranslateUi(loeMovieMakerTools);

        QMetaObject::connectSlotsByName(loeMovieMakerTools);
    } // setupUi

    void retranslateUi(QWidget *loeMovieMakerTools)
    {
        loeMovieMakerTools->setWindowTitle(QApplication::translate("loeMovieMakerTools", "LoE Movie Maker Tools", 0));
        label->setText(QApplication::translate("loeMovieMakerTools", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">These are some tools to help you make your own Legends <br/> of Equestria Bloopers and Machinima, they are pretty <br/> limiting, but it is what was possible to gather off the client. <br/><br/> Some of these require a player to be set.</p></body></html>", 0));
        groupBox->setTitle(QApplication::translate("loeMovieMakerTools", "Command Settings", 0));
        label_2->setText(QApplication::translate("loeMovieMakerTools", "!anhero Delay", 0));
        spinBox->setSuffix(QApplication::translate("loeMovieMakerTools", "ms", 0));
        pushButton->setText(QApplication::translate("loeMovieMakerTools", "Apply Settings", 0));
        groupBox_2->setTitle(QApplication::translate("loeMovieMakerTools", "Pony Settings and Controls", 0));
        lineEdit->setText(QApplication::translate("loeMovieMakerTools", "Disabled till fixed", 0));
        pushButton_2->setText(QApplication::translate("loeMovieMakerTools", "Send ponyData", 0));
        label_3->setText(QApplication::translate("loeMovieMakerTools", "Made for debugging only, but hey, they  are useful.", 0));
        pushButton_3->setText(QApplication::translate("loeMovieMakerTools", "Clone/Instantiate Player", 0));
        label_4->setText(QApplication::translate("loeMovieMakerTools", "<html><head/><body><p align=\"center\">Leave empty to clone on the player's current position. <br/>Otherwise, type in the necesary arguments. <br/> <br/>Args (in order): <br/> [key] [netviewId] [viewId] [x] [y] [z] [rx] [ry] [rz]</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class loeMovieMakerTools: public Ui_loeMovieMakerTools {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOEMOVIEMAKERTOOLS_H
