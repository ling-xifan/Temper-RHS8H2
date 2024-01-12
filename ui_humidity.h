/********************************************************************************
** Form generated from reading UI file 'humidity.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HUMIDITY_H
#define UI_HUMIDITY_H

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

class Ui_Humidity
{
public:
    QWidget *centralwidget;
    QLabel *label_3;
    QPushButton *pushSendMinX;
    QLabel *label_7;
    QLineEdit *lineminY;
    QLineEdit *linemaxY;
    QLineEdit *lineminX;
    QPushButton *pushSendMaxX;
    QPushButton *pushSendMaxY;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *linemaxX;
    QLabel *label_8;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushSendMinY;
    QLabel *label_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Humidity)
    {
        if (Humidity->objectName().isEmpty())
            Humidity->setObjectName(QStringLiteral("Humidity"));
        Humidity->resize(800, 600);
        centralwidget = new QWidget(Humidity);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 480, 50, 25));
        pushSendMinX = new QPushButton(centralwidget);
        pushSendMinX->setObjectName(QStringLiteral("pushSendMinX"));
        pushSendMinX->setGeometry(QRect(590, 510, 70, 25));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(400, 510, 50, 25));
        lineminY = new QLineEdit(centralwidget);
        lineminY->setObjectName(QStringLiteral("lineminY"));
        lineminY->setGeometry(QRect(460, 480, 113, 25));
        linemaxY = new QLineEdit(centralwidget);
        linemaxY->setObjectName(QStringLiteral("linemaxY"));
        linemaxY->setGeometry(QRect(170, 480, 113, 25));
        lineminX = new QLineEdit(centralwidget);
        lineminX->setObjectName(QStringLiteral("lineminX"));
        lineminX->setGeometry(QRect(460, 510, 113, 25));
        pushSendMaxX = new QPushButton(centralwidget);
        pushSendMaxX->setObjectName(QStringLiteral("pushSendMaxX"));
        pushSendMaxX->setGeometry(QRect(300, 510, 70, 25));
        pushSendMaxY = new QPushButton(centralwidget);
        pushSendMaxY->setObjectName(QStringLiteral("pushSendMaxY"));
        pushSendMaxY->setGeometry(QRect(300, 480, 70, 25));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(400, 480, 50, 25));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 480, 71, 25));
        linemaxX = new QLineEdit(centralwidget);
        linemaxX->setObjectName(QStringLiteral("linemaxX"));
        linemaxX->setGeometry(QRect(170, 510, 113, 25));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 510, 71, 25));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 40, 761, 421));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushSendMinY = new QPushButton(centralwidget);
        pushSendMinY->setObjectName(QStringLiteral("pushSendMinY"));
        pushSendMinY->setGeometry(QRect(590, 480, 70, 25));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(110, 510, 50, 25));
        Humidity->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Humidity);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        Humidity->setMenuBar(menubar);
        statusbar = new QStatusBar(Humidity);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Humidity->setStatusBar(statusbar);

        retranslateUi(Humidity);

        QMetaObject::connectSlotsByName(Humidity);
    } // setupUi

    void retranslateUi(QMainWindow *Humidity)
    {
        Humidity->setWindowTitle(QApplication::translate("Humidity", "MainWindow", nullptr));
        label_3->setText(QApplication::translate("Humidity", "\346\234\200\345\244\247\345\200\274", nullptr));
        pushSendMinX->setText(QApplication::translate("Humidity", "\345\217\221\351\200\201", nullptr));
        label_7->setText(QApplication::translate("Humidity", "\346\234\200\345\260\217\345\200\274", nullptr));
        pushSendMaxX->setText(QApplication::translate("Humidity", "\345\217\221\351\200\201", nullptr));
        pushSendMaxY->setText(QApplication::translate("Humidity", "\345\217\221\351\200\201", nullptr));
        label_4->setText(QApplication::translate("Humidity", "\346\234\200\345\260\217\345\200\274", nullptr));
        label_5->setText(QApplication::translate("Humidity", "\346\271\277\345\272\246\350\214\203\345\233\264", nullptr));
        label_8->setText(QApplication::translate("Humidity", "\346\227\266\351\227\264\350\214\203\345\233\264", nullptr));
        pushSendMinY->setText(QApplication::translate("Humidity", "\345\217\221\351\200\201", nullptr));
        label_6->setText(QApplication::translate("Humidity", "\346\234\200\345\244\247\345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Humidity: public Ui_Humidity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HUMIDITY_H
