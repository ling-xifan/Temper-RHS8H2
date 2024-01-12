#include "humidity.h"
#include "ui_humidity.h"

using std::vector;

extern vector<float> RH_signal;//湿度数组
static QColor Graph_color[2] = {
                         QColor(255, 0, 0),//大红
                         QColor(0, 255, 0)
                       };
void idleThread() {
    //空线程函数
}
// 重写 closeEvent：确认退出对话框
void Humidity::closeEvent(QCloseEvent* event){
    if (openflag_){
        delete series_[1];
        delete array_graph_; // 删除线程
        timer_->stop();
        delete timer_; // 删除定时器
    }
    event->accept(); // 接受退出信号，程序退出
}

void Humidity::drawThread() {
    series_[1]->setPen(QPen(Graph_color[1], 3, Qt::SolidLine)); // 设置折线显示效果
    for (int i = 0; i <= axisX_max_; i++) {
        series_[1]->append(-i, RH_signal[i]);
    }

    return;
}


Humidity::Humidity(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::Humidity)
{
    openflag_ = 0;
    axisX_max_ = 50;
    axisX_min_ = 0;
    axisY_max_ = 100;
    axisY_min_ = 0;
    ui_->setupUi(this);
    humidityInit();
}

Humidity::~Humidity()
{
    delete ui_;
}
void Humidity::humidityInit() {

    /*****************设置标题和图标***********************/
    setWindowTitle(u8"湿度显示");
    drawing_ = new QChart;
    drawing_->setTitle(u8"湿度");
    drawview_ = new QChartView(drawing_);
    axisX_ = new QValueAxis;
    axisY_ = new QValueAxis;

    //建立坐标轴
    QBrush AxisColor1;
    AxisColor1.setColor(Qt::black);
    axisX_->setRange(-axisX_max_, axisX_min_);                // 设置范围
    axisX_->setLabelFormat("%d");                            // 设置刻度的格式
    axisX_->setGridLineVisible(true);                        // 网格线可见
    axisX_->setTickCount(6);                                 // 设置多少个大格
    axisX_->setMinorTickCount(1);                            // 设置每个大格里面小刻度线的数目
    axisX_->setTitleText(u8"time");                             // 设置描述

    axisY_->setRange(axisY_min_, axisY_max_);
    axisY_->setLabelFormat("%.1f");
    axisY_->setGridLineVisible(true);
    axisY_->setTickCount(8);
    axisY_->setMinorTickCount(1);
    axisY_->setTitleText(u8"RH/%");

    //为曲线添加坐标轴
    drawing_->addAxis(axisX_, Qt::AlignBottom);               // 下：Qt::AlignBottom  上：Qt::AlignTop
    drawing_->addAxis(axisY_, Qt::AlignLeft);                 // 左：Qt::AlignLeft    右：Qt::AlignRight
    drawing_->legend()->setAlignment(Qt::AlignTop);
    drawing_->legend()->setVisible(false);
    drawview_->setRenderHint(QPainter::Antialiasing);        //防止图形走样
    ui_->verticalLayout_2->addWidget(drawview_);//将图像放入布局中

    //连接信号和槽
    connect(ui_->pushSendMaxY,&QPushButton::clicked,this,&Humidity::setMaxYRange);
    connect(ui_->pushSendMinY,&QPushButton::clicked,this,&Humidity::setMinYRange);
    connect(ui_->pushSendMaxX,&QPushButton::clicked,this,&Humidity::setMaxXRange);
    connect(ui_->pushSendMinX,&QPushButton::clicked,this,&Humidity::setMinXRange);
}

void Humidity::drawRHBegin(){

timer_ = new QTimer;
timer_->start(TIME_SEND);
openflag_ = 1;
series_[1] = new QLineSeries;
     array_graph_= new std::thread(idleThread);//创建空闲线程
    array_graph_->join();
    connect(timer_, &QTimer::timeout, this, &Humidity::drawGraph);//连接定时器

}
void Humidity::drawGraph(){

    delete array_graph_;
    delete series_[1];
    array_graph_ = new std::thread(&Humidity::drawThread, this); // 创建画图线程

    series_[1] = new QLineSeries;
    array_graph_->join();
    drawing_->addSeries(series_[1]);
    drawing_->setAxisX(axisX_, series_[1]);
    drawing_->setAxisY(axisY_, series_[1]);
}

/*************功能：坐标轴手动设置**********************/
void Humidity::setMaxYRange() {

    if (!ui_->linemaxY->text().isEmpty()) // 设置内容不能为空
    {
        axisY_max_ = ui_->linemaxY->text().toInt(); // 将文本框中内容转换为int数据
        axisY_->setRange(axisY_min_, axisY_max_); // 设置范围
    }
}

/*************功能：坐标轴手动设置**********************/
void Humidity::setMinYRange() {

    if (!ui_->lineminY->text().isEmpty())
    {
        axisY_min_ = ui_->lineminY->text().toInt();
        axisY_->setRange(axisY_min_, axisY_max_);
    }
}

/*************功能：坐标轴手动设置**********************/
void Humidity::setMaxXRange() {

    if (!ui_->linemaxX->text().isEmpty()) // 设置内容不能为空
    {
        axisX_max_ = ui_->linemaxX->text().toInt(); // 将文本框中内容转换为int数据
        axisX_->setRange(-axisX_max_, -axisX_min_); // 设置范围
    }
}

/*************功能：坐标轴手动设置**********************/
void Humidity::setMinXRange() {

    if (!ui_->lineminX->text().isEmpty())
    {
        axisX_min_ = ui_->lineminX->text().toInt();
        axisX_->setRange(-axisX_max_, -axisX_min_); // 设置范围
    }
}

