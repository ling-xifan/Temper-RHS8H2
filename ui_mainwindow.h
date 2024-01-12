/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_txt;
    QAction *action_excel;
    QAction *action_graph;
    QWidget *centralWidget;
    QPushButton *pushStart;
    QPushButton *pushClear;
    QListView *list_ch2;
    QListView *list_ch1;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_5;
    QListView *list_ch3;
    QFrame *line_2;
    QPushButton *pushStop;
    QLabel *label_temperature;
    QComboBox *comboVolt1;
    QFrame *line;
    QListView *list_ch6;
    QListView *list_ch4;
    QListView *list_ch5;
    QListView *list_ch8;
    QListView *list_ch7;
    QPushButton *pushOpen;
    QPushButton *pushClose;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_17;
    QCheckBox *checkBox_18;
    QCheckBox *checkBox_autoset;
    QLineEdit *linemax;
    QLineEdit *linemin;
    QPushButton *pushSendMax;
    QPushButton *pushSendMin;
    QLabel *label_3;
    QLabel *label_4;
    QListView *Temperature;
    QListView *list_RH;
    QLabel *label_temperature_2;
    QLabel *label_temperature_3;
    QPushButton *push_view;
    QPushButton *push_view_2;
    QLineEdit *linemintime;
    QPushButton *pushSendMin_2;
    QLabel *label_5;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1261, 689);
        action_txt = new QAction(MainWindow);
        action_txt->setObjectName(QString::fromUtf8("action_txt"));
        action_excel = new QAction(MainWindow);
        action_excel->setObjectName(QString::fromUtf8("action_excel"));
        action_graph = new QAction(MainWindow);
        action_graph->setObjectName(QString::fromUtf8("action_graph"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushStart = new QPushButton(centralWidget);
        pushStart->setObjectName(QString::fromUtf8("pushStart"));
        pushStart->setGeometry(QRect(1090, 340, 111, 61));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        pushStart->setFont(font);
        pushClear = new QPushButton(centralWidget);
        pushClear->setObjectName(QString::fromUtf8("pushClear"));
        pushClear->setGeometry(QRect(1090, 520, 111, 61));
        pushClear->setFont(font);
        list_ch2 = new QListView(centralWidget);
        list_ch2->setObjectName(QString::fromUtf8("list_ch2"));
        list_ch2->setGeometry(QRect(530, 30, 91, 25));
        QFont font1;
        font1.setPointSize(11);
        list_ch2->setFont(font1);
        list_ch1 = new QListView(centralWidget);
        list_ch1->setObjectName(QString::fromUtf8("list_ch1"));
        list_ch1->setGeometry(QRect(390, 30, 91, 25));
        list_ch1->setFont(font1);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 110, 981, 451));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        list_ch3 = new QListView(centralWidget);
        list_ch3->setObjectName(QString::fromUtf8("list_ch3"));
        list_ch3->setGeometry(QRect(670, 30, 91, 25));
        list_ch3->setFont(font1);
        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(270, 0, 20, 100));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushStop = new QPushButton(centralWidget);
        pushStop->setObjectName(QString::fromUtf8("pushStop"));
        pushStop->setGeometry(QRect(1090, 430, 111, 61));
        pushStop->setFont(font);
        label_temperature = new QLabel(centralWidget);
        label_temperature->setObjectName(QString::fromUtf8("label_temperature"));
        label_temperature->setGeometry(QRect(1150, 30, 71, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(11);
        label_temperature->setFont(font2);
        comboVolt1 = new QComboBox(centralWidget);
        comboVolt1->addItem(QString());
        comboVolt1->setObjectName(QString::fromUtf8("comboVolt1"));
        comboVolt1->setGeometry(QRect(1050, 30, 81, 31));
        comboVolt1->setFont(font2);
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(1010, 0, 20, 601));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        list_ch6 = new QListView(centralWidget);
        list_ch6->setObjectName(QString::fromUtf8("list_ch6"));
        list_ch6->setGeometry(QRect(530, 70, 91, 25));
        list_ch6->setFont(font1);
        list_ch4 = new QListView(centralWidget);
        list_ch4->setObjectName(QString::fromUtf8("list_ch4"));
        list_ch4->setGeometry(QRect(810, 30, 91, 25));
        list_ch4->setFont(font1);
        list_ch5 = new QListView(centralWidget);
        list_ch5->setObjectName(QString::fromUtf8("list_ch5"));
        list_ch5->setGeometry(QRect(390, 70, 91, 25));
        list_ch5->setFont(font1);
        list_ch8 = new QListView(centralWidget);
        list_ch8->setObjectName(QString::fromUtf8("list_ch8"));
        list_ch8->setGeometry(QRect(810, 70, 91, 25));
        list_ch8->setFont(font1);
        list_ch7 = new QListView(centralWidget);
        list_ch7->setObjectName(QString::fromUtf8("list_ch7"));
        list_ch7->setGeometry(QRect(670, 70, 91, 25));
        list_ch7->setFont(font1);
        pushOpen = new QPushButton(centralWidget);
        pushOpen->setObjectName(QString::fromUtf8("pushOpen"));
        pushOpen->setGeometry(QRect(1090, 160, 111, 61));
        pushOpen->setFont(font);
        pushClose = new QPushButton(centralWidget);
        pushClose->setObjectName(QString::fromUtf8("pushClose"));
        pushClose->setGeometry(QRect(1090, 250, 111, 61));
        pushClose->setFont(font);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(350, 30, 71, 25));
        QFont font3;
        font3.setBold(true);
        font3.setWeight(75);
        checkBox->setFont(font3);
        checkBox->setChecked(true);
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(490, 30, 71, 25));
        checkBox_2->setFont(font3);
        checkBox_2->setChecked(true);
        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(630, 30, 71, 25));
        checkBox_3->setFont(font3);
        checkBox_3->setChecked(true);
        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(770, 30, 71, 25));
        checkBox_4->setFont(font3);
        checkBox_4->setChecked(true);
        checkBox_5 = new QCheckBox(centralWidget);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(350, 70, 71, 25));
        checkBox_5->setFont(font3);
        checkBox_5->setChecked(true);
        checkBox_5->setTristate(false);
        checkBox_6 = new QCheckBox(centralWidget);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setGeometry(QRect(490, 70, 71, 25));
        checkBox_6->setFont(font3);
        checkBox_6->setChecked(true);
        checkBox_7 = new QCheckBox(centralWidget);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(630, 70, 71, 25));
        checkBox_7->setFont(font3);
        checkBox_7->setChecked(true);
        checkBox_8 = new QCheckBox(centralWidget);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(770, 70, 71, 25));
        checkBox_8->setFont(font3);
        checkBox_8->setChecked(true);
        checkBox_17 = new QCheckBox(centralWidget);
        checkBox_17->setObjectName(QString::fromUtf8("checkBox_17"));
        checkBox_17->setGeometry(QRect(950, 30, 50, 21));
        checkBox_17->setChecked(true);
        checkBox_18 = new QCheckBox(centralWidget);
        checkBox_18->setObjectName(QString::fromUtf8("checkBox_18"));
        checkBox_18->setGeometry(QRect(950, 70, 50, 21));
        checkBox_18->setChecked(true);
        checkBox_autoset = new QCheckBox(centralWidget);
        checkBox_autoset->setObjectName(QString::fromUtf8("checkBox_autoset"));
        checkBox_autoset->setGeometry(QRect(20, 570, 151, 25));
        checkBox_autoset->setChecked(true);
        linemax = new QLineEdit(centralWidget);
        linemax->setObjectName(QString::fromUtf8("linemax"));
        linemax->setGeometry(QRect(230, 570, 113, 25));
        linemin = new QLineEdit(centralWidget);
        linemin->setObjectName(QString::fromUtf8("linemin"));
        linemin->setGeometry(QRect(490, 570, 113, 25));
        pushSendMax = new QPushButton(centralWidget);
        pushSendMax->setObjectName(QString::fromUtf8("pushSendMax"));
        pushSendMax->setGeometry(QRect(350, 570, 70, 25));
        pushSendMin = new QPushButton(centralWidget);
        pushSendMin->setObjectName(QString::fromUtf8("pushSendMin"));
        pushSendMin->setGeometry(QRect(610, 570, 70, 25));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 570, 61, 25));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(429, 570, 61, 25));
        Temperature = new QListView(centralWidget);
        Temperature->setObjectName(QString::fromUtf8("Temperature"));
        Temperature->setGeometry(QRect(10, 20, 81, 25));
        Temperature->setFont(font1);
        list_RH = new QListView(centralWidget);
        list_RH->setObjectName(QString::fromUtf8("list_RH"));
        list_RH->setGeometry(QRect(10, 60, 81, 25));
        list_RH->setFont(font1);
        label_temperature_2 = new QLabel(centralWidget);
        label_temperature_2->setObjectName(QString::fromUtf8("label_temperature_2"));
        label_temperature_2->setGeometry(QRect(110, 20, 21, 31));
        label_temperature_2->setFont(font2);
        label_temperature_3 = new QLabel(centralWidget);
        label_temperature_3->setObjectName(QString::fromUtf8("label_temperature_3"));
        label_temperature_3->setGeometry(QRect(110, 60, 21, 31));
        label_temperature_3->setFont(font2);
        push_view = new QPushButton(centralWidget);
        push_view->setObjectName(QString::fromUtf8("push_view"));
        push_view->setGeometry(QRect(160, 20, 70, 25));
        push_view_2 = new QPushButton(centralWidget);
        push_view_2->setObjectName(QString::fromUtf8("push_view_2"));
        push_view_2->setGeometry(QRect(160, 60, 70, 25));
        linemintime = new QLineEdit(centralWidget);
        linemintime->setObjectName(QString::fromUtf8("linemintime"));
        linemintime->setGeometry(QRect(800, 570, 113, 25));
        pushSendMin_2 = new QPushButton(centralWidget);
        pushSendMin_2->setObjectName(QString::fromUtf8("pushSendMin_2"));
        pushSendMin_2->setGeometry(QRect(930, 570, 70, 25));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(719, 570, 71, 25));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1261, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_excel);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_txt->setText(QCoreApplication::translate("MainWindow", "save as txt", nullptr));
        action_excel->setText(QCoreApplication::translate("MainWindow", "save as excel", nullptr));
        action_graph->setText(QCoreApplication::translate("MainWindow", "save as graph", nullptr));
        pushStart->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\351\207\207\351\233\206", nullptr));
        pushClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        pushStop->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\351\207\207\351\233\206", nullptr));
        label_temperature->setText(QCoreApplication::translate("MainWindow", "\344\270\262\345\217\243\345\217\267", nullptr));
        comboVolt1->setItemText(0, QCoreApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251", nullptr));

        pushOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushClose->setText(QCoreApplication::translate("MainWindow", "\345\205\263\351\227\255\344\270\262\345\217\243", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        checkBox_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        checkBox_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        checkBox_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        checkBox_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        checkBox_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        checkBox_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        checkBox_17->setText(QCoreApplication::translate("MainWindow", "ALL", nullptr));
        checkBox_18->setText(QCoreApplication::translate("MainWindow", "ALL", nullptr));
        checkBox_autoset->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\350\256\276\347\275\256\345\235\220\346\240\207", nullptr));
        pushSendMax->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        pushSendMin->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\244\247\345\200\274", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\260\217\345\200\274", nullptr));
        label_temperature_2->setText(QCoreApplication::translate("MainWindow", "\342\204\203", nullptr));
        label_temperature_3->setText(QCoreApplication::translate("MainWindow", "%", nullptr));
        push_view->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213", nullptr));
        push_view_2->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213", nullptr));
        pushSendMin_2->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\227\266\351\227\264\350\214\203\345\233\264", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
