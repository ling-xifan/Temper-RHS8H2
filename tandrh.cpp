#include "tandrh.h"
#include "ui_tandrh.h"


using std::vector;
using std::thread;
extern vector<float> Temperature_signal;    //时间数组
static QColor Graph_color[2] = {
                         QColor(255, 0, 0),//大红
                         QColor(0, 255, 0)
                       };
void idle_thread1() {
    //空线程函数
}


void TandRH::drawThread() {
    // 设置曲线显示
    series_[0]->setPen(QPen(Graph_color[0], 3, Qt::SolidLine));
    for (int i = 0; i <= TandRH::axisX_max_; i++) {
        series_[0]->append(-i, Temperature_signal[i]);
    }
    return;
}
// 重写closeEvent: 确认退出对话框
void TandRH::closeEvent(QCloseEvent *event) {
    if (openflag_) {
        delete series_[0];
        delete array_graph_; // 删除线程
        draw_timer_->stop();
        openflag_ = 0;
        delete draw_timer_; // 删除采集线程
    }
     event->accept(); // 接受退出信号，程序退出
}

TandRH::TandRH(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::TandRH)
{
    openflag_ = 0;
    axisX_max_ = 50;
    axisX_min_ = 0;
    axisY_max_ = 50;
    axisY_min_ = 10;
    ui_->setupUi(this);
    temperatureInit();

}

TandRH::~TandRH()
{
    delete ui_;
}
void TandRH::temperatureInit()
{
    /*****************设置标题和图标***********************/
    setWindowTitle(u8"温度显示");
    drawing_ = new QChart;
    drawing_->setTitle(u8"温度");
    drawview_ = new QChartView(drawing_);
    axisX_ = new QValueAxis;
    axisY_ = new QValueAxis;
    //建立数据源队列

    //建立坐标轴
    QBrush AxisColor1;
    AxisColor1.setColor(Qt::black);
    axisX_->setRange(-axisX_max_, axisX_min_);                // 设置范围
    axisX_->setLabelFormat("%d");             // 设置刻度的格式
    axisX_->setGridLineVisible(true);         // 网格线可见
    axisX_->setTickCount(6);                  // 设置多少个大格
    axisX_->setMinorTickCount(1);             // 设置每个大格里面小刻度线的数目
    axisX_->setTitleText(u8"time");           // 设置描述

    axisY_->setRange(axisY_min_, axisY_max_);
    axisY_->setLabelFormat("%.1f");
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(8);
    axisY_->setMinorTickCount(1);
    axisY_->setTitleText(u8"T/℃");

    //为曲线添加坐标轴
    drawing_->addAxis(axisX_, Qt::AlignBottom);               // 下：Qt::AlignBottom  上：Qt::AlignTop
    drawing_->addAxis(axisY_, Qt::AlignLeft);                 // 左：Qt::AlignLeft    右：Qt::AlignRight
    drawing_->legend()->setAlignment(Qt::AlignTop);
    drawing_->legend()->setVisible(false);
    drawview_->setRenderHint(QPainter::Antialiasing);        //防止图形走样
    ui_->verticalLayout->addWidget(drawview_);                //将图像放入布局中
    connect(ui_->pushSendMaxY,&QPushButton::clicked,this,&TandRH::setMaxYRange);
    connect(ui_->pushSendMinY,&QPushButton::clicked,this,&TandRH::setMinYRange);
    connect(ui_->pushSendMaxX,&QPushButton::clicked,this,&TandRH::setMaxXRange);
    connect(ui_->pushSendMinX,&QPushButton::clicked,this,&TandRH::setMinXRange);
}

void TandRH::drawBegin() {
    draw_timer_ = new QTimer;
    draw_timer_->start(TIME_SEND);
    openflag_ = 1;
    series_[0] = new QLineSeries;
    // 创建空闲线程
    array_graph_ = new std::thread(idle_thread1);
    array_graph_->join();
    // 连接定时器
    connect(draw_timer_, &QTimer::timeout, this, &TandRH::drawGraph);
}

void TandRH::drawGraph()
{

    delete array_graph_;
    delete series_[0];

    //创建画图线程
    array_graph_ = new std::thread(&TandRH::drawThread, this);
    array_graph_->join();

    series_[0] = new QLineSeries;
    drawing_->addSeries(series_[0]);
    drawing_->setAxisX(axisX_, series_[0]);
    drawing_->setAxisY(axisY_, series_[0]);
}
/*************功能：Y坐标轴手动设置**********************/
void TandRH::setMaxYRange()
{
     //设置内容不能为空
     if(!ui_->linemaxY->text().isEmpty()){
        //将文本框中内容转换为int数据
         axisY_max_ = ui_->linemaxY->text().toInt();
         axisY_->setRange(axisY_min_, axisY_max_);
      }

}
/*************功能：Y坐标轴手动设置**********************/
void TandRH::setMinYRange()
{
     if(!ui_->lineminY->text().isEmpty()){
        axisY_min_ = ui_->lineminY->text().toInt();
        axisY_->setRange(axisY_min_, axisY_max_);
     }
}
/*************功能：X坐标轴手动设置**********************/
void TandRH::setMaxXRange()
{
    if (!ui_->linemaxX->text().isEmpty()) {
        axisX_max_ = ui_->linemaxX->text().toInt(); // 将文本框中内容转换为int数据
        axisX_->setRange(-axisX_max_, -axisX_min_); // 设置范围
    }
}

/*************功能：X坐标轴手动设置**********************/
void TandRH::setMinXRange()
{
    if (!ui_->lineminX->text().isEmpty()) {
        axisX_min_ = ui_->lineminX->text().toInt();
        axisX_->setRange(-axisX_max_, -axisX_min_); // 设置范围
    }
}

