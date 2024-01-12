/********************************************************************************
** Form generated from reading UI file 'tandrh.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TANDRH_H
#define UI_TANDRH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TandRH
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *linemaxY;
    QLabel *label_3;
    QPushButton *pushSendMaxY;
    QLineEdit *lineminY;
    QLabel *label_4;
    QPushButton *pushSendMinY;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineminX;
    QLineEdit *linemaxX;
    QPushButton *pushSendMaxX;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushSendMinX;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TandRH)
    {
        if (TandRH->objectName().isEmpty())
            TandRH->setObjectName(QString::fromUtf8("TandRH"));
        TandRH->resize(800, 600);
        centralwidget = new QWidget(TandRH);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 50, 761, 421));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        linemaxY = new QLineEdit(centralwidget);
        linemaxY->setObjectName(QString::fromUtf8("linemaxY"));
        linemaxY->setGeometry(QRect(170, 490, 113, 25));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(110, 490, 50, 25));
        pushSendMaxY = new QPushButton(centralwidget);
        pushSendMaxY->setObjectName(QString::fromUtf8("pushSendMaxY"));
        pushSendMaxY->setGeometry(QRect(300, 490, 70, 25));
        lineminY = new QLineEdit(centralwidget);
        lineminY->setObjectName(QString::fromUtf8("lineminY"));
        lineminY->setGeometry(QRect(460, 490, 113, 25));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(400, 490, 50, 25));
        pushSendMinY = new QPushButton(centralwidget);
        pushSendMinY->setObjectName(QString::fromUtf8("pushSendMinY"));
        pushSendMinY->setGeometry(QRect(590, 490, 70, 25));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 490, 71, 25));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(110, 520, 50, 25));
        lineminX = new QLineEdit(centralwidget);
        lineminX->setObjectName(QString::fromUtf8("lineminX"));
        lineminX->setGeometry(QRect(460, 520, 113, 25));
        linemaxX = new QLineEdit(centralwidget);
        linemaxX->setObjectName(QString::fromUtf8("linemaxX"));
        linemaxX->setGeometry(QRect(170, 520, 113, 25));
        pushSendMaxX = new QPushButton(centralwidget);
        pushSendMaxX->setObjectName(QString::fromUtf8("pushSendMaxX"));
        pushSendMaxX->setGeometry(QRect(300, 520, 70, 25));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(400, 520, 50, 25));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 520, 71, 25));
        pushSendMinX = new QPushButton(centralwidget);
        pushSendMinX->setObjectName(QString::fromUtf8("pushSendMinX"));
        pushSendMinX->setGeometry(QRect(590, 520, 70, 25));
        TandRH->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TandRH);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        TandRH->setMenuBar(menubar);
        statusbar = new QStatusBar(TandRH);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TandRH->setStatusBar(statusbar);

        retranslateUi(TandRH);

        QMetaObject::connectSlotsByName(TandRH);
    } // setupUi

    void retranslateUi(QMainWindow *TandRH)
    {
        TandRH->setWindowTitle(QCoreApplication::translate("TandRH", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("TandRH", "\346\234\200\345\244\247\345\200\274", nullptr));
        pushSendMaxY->setText(QCoreApplication::translate("TandRH", "\345\217\221\351\200\201", nullptr));
        label_4->setText(QCoreApplication::translate("TandRH", "\346\234\200\345\260\217\345\200\274", nullptr));
        pushSendMinY->setText(QCoreApplication::translate("TandRH", "\345\217\221\351\200\201", nullptr));
        label_5->setText(QCoreApplication::translate("TandRH", "\346\270\251\345\272\246\350\214\203\345\233\264", nullptr));
        label_6->setText(QCoreApplication::translate("TandRH", "\346\234\200\345\244\247\345\200\274", nullptr));
        pushSendMaxX->setText(QCoreApplication::translate("TandRH", "\345\217\221\351\200\201", nullptr));
        label_7->setText(QCoreApplication::translate("TandRH", "\346\234\200\345\260\217\345\200\274", nullptr));
        label_8->setText(QCoreApplication::translate("TandRH", "\346\227\266\351\227\264\350\214\203\345\233\264", nullptr));
        pushSendMinX->setText(QCoreApplication::translate("TandRH", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TandRH: public Ui_TandRH {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANDRH_H
