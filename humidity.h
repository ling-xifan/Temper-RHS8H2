#ifndef HUMIDITY_H
#define HUMIDITY_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QMessageBox>
#include <vector>
#include <QStringListModel>
#include <QStringList>
#include <QDebug>
#include <thread>
#include <mutex>
#include <QTimer>
#include <QCloseEvent>

#define TIME_SEND 500

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

    void drawRHBegin();
private:

    int openflag_;
    int axisY_max_,axisY_min_;
    int axisX_max_,axisX_min_;
    std::thread* array_graph_;
    Ui::Humidity *ui_;
    QChartView *drawview_;
    QValueAxis *axisX_;
    QValueAxis *axisY_;
    QChart *drawing_;
    QLineSeries* series_[2];
    QTimer *timer_;

    void humidityInit();
    void drawThread();
    // 重写closeEvent的申明
    void closeEvent(QCloseEvent *event);
private slots:
    void drawGraph();
    void setMaxYRange();
    void setMinYRange();
    void setMaxXRange();
    void setMinXRange();
};

#endif // HUMIDITY_H
