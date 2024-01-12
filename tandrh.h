#ifndef TANDRH_H
#define TANDRH_H
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
#include <QTime>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtDebug>
#include <QCloseEvent>

#define TIME_SEND 500

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
    void drawBegin();

private:
    int openflag_;
    int axisY_max_,axisY_min_ ;
    int axisX_max_,axisX_min_ ;
    std::thread* array_graph_;
    Ui::TandRH *ui_;
    QChartView *drawview_;
    QValueAxis *axisX_;
    QValueAxis *axisY_;
    QChart *drawing_;
    QLineSeries* series_[2];
    QTimer *draw_timer_;
    void drawThread();
    void temperatureInit();
    void closeEvent(QCloseEvent *event);    // 重写closeEvent的申明
private slots:
    void drawGraph();
    void setMaxYRange();
    void setMinYRange();
    void setMaxXRange();
    void setMinXRange();

};

#endif // TANDRH_H
