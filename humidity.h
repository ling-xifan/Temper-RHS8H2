#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QMessageBox>
#include <QtNetwork/QTcpServer>                 //监听套接字
#include <QtNetwork/QTcpSocket>                 //通信套接字//对方的(客户端的)套接字(通信套接字)
#include <vector>
#include <QStringListModel>
#include <QStringList>

#include <QDebug>
#include <thread>
#include <mutex>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QSerialPort>
#include <QtDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QStringList>
#include <QCloseEvent>

QT_CHARTS_USE_NAMESPACE
QT_BEGIN_NAMESPACE
namespace Ui {
class Humidity;
}
QT_END_NAMESPACE
class Humidity : public QMainWindow
{
    Q_OBJECT

public:
    explicit Humidity(QWidget *parent = 0);
    ~Humidity();
    QValueAxis *axisX2;
    QValueAxis *axisY2;
    QChart *drawing2;
    QLineSeries* series2[2];
    QTimer *timer3;
    void Humidity_init();
    void drawRH_begin();
private:
    Ui::Humidity *ui;
    QChartView *drawview2;
    void draw_thread2();
     void closeEvent(QCloseEvent *event);    // 重写closeEvent的申明
private slots:
    void Draw_Graph2();
    void Set_MaxY_Range();
    void Set_MinY_Range();
    void Set_MaxX_Range();
    void Set_MinX_Range();
};

#endif // HUMIDITY_H
