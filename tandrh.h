#ifndef TANDRH_H
#define TANDRH_H
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
class TandRH;
}
QT_END_NAMESPACE
class TandRH : public QMainWindow
{
    Q_OBJECT
public:
    explicit TandRH(QWidget *parent = 0);
    ~TandRH();
    QValueAxis *axisX1;
    QValueAxis *axisY1;
    QChart *drawing1;
    QLineSeries* series1 [2];
    QTimer *timer2;
     void temperature_init();
     void draw_begin();

private:
    Ui::TandRH *ui;
    QChartView *drawview1;
    void draw_thread1();
 void closeEvent(QCloseEvent *event);    // 重写closeEvent的申明
private slots:
    void Draw_Graph1();
    void Set_MaxY_Range();
    void Set_MinY_Range();
    void Set_MaxX_Range();
    void Set_MinX_Range();

};

#endif // TANDRH_H
