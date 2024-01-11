#include "tandrh.h"
#include "ui_tandrh.h"
#include "mainwindow.h"
using namespace std;


extern vector<float> Temperature_signal;    //时间数组
extern std::mutex bMutex;//
extern int reading;
static int openflag = 0;
static int axisY_max = 30,axisY_min = 10;
static int axisX_max = 500,axisX_min = 0;
static thread* array_graph1;
static QColor Graph_color[2] = {
                         QColor(255, 0, 0),//大红
                         QColor(0, 255, 0)
                       };
void idle_thread1() {
    //空线程函数
}


void TandRH::draw_thread1() {
    qDebug() <<"start:drawT";
    while(reading);//等待读结束
  //  bMutex.lock();
        series1[0]->setPen(QPen(Graph_color[0], 3, Qt::SolidLine));// 设置折线显示效果
        for (int i = 0; i <= axisX_max; i++)
           series1[0]->append(-i, Temperature_signal[i]);

    return;
   // bMutex.unlock();
}
// 重写closeEvent: 确认退出对话框
void TandRH::closeEvent(QCloseEvent *event)
{
if(openflag)
{
        // bMutex.unlock();
      delete series1[0];
    delete array_graph1;//删除线程
    timer2->stop();
    delete timer2;//删除采集线程

}

 event->accept(); // 接受退出信号，程序退出
}
TandRH::TandRH(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TandRH)
{
    ui->setupUi(this);
    temperature_init();

    /*****************设置标题和图标***********************/
    setWindowTitle(u8"Temperature");

    drawing1 = new QChart;
    drawing1->setTitle(u8"Temperature");
    drawview1 = new QChartView(drawing1);
    axisX1 = new QValueAxis;
    axisY1 = new QValueAxis;
    //建立数据源队列

    //建立坐标轴
    QBrush AxisColor1;
    AxisColor1.setColor(Qt::black);
    axisX1->setRange(-500, 0);                // 设置范围
    axisX1->setLabelFormat("%d");                            // 设置刻度的格式
    axisX1->setGridLineVisible(true);                        // 网格线可见
    axisX1->setTickCount(6);                                 // 设置多少个大格
    axisX1->setMinorTickCount(1);                            // 设置每个大格里面小刻度线的数目
    axisX1->setTitleText(u8"time");                             // 设置描述

    axisY1->setRange(10, 30);
    axisY1->setLabelFormat("%.1f");
    axisY1->setGridLineVisible(true);
    axisY1->setTickCount(8);
    axisY1->setMinorTickCount(1);
    axisY1->setTitleText(u8"T/℃");

    //为曲线添加坐标轴
    drawing1->addAxis(axisX1, Qt::AlignBottom);               // 下：Qt::AlignBottom  上：Qt::AlignTop
    drawing1->addAxis(axisY1, Qt::AlignLeft);                 // 左：Qt::AlignLeft    右：Qt::AlignRight
    drawing1->legend()->setAlignment(Qt::AlignTop);
    drawing1->legend()->setVisible(false);
    drawview1->setRenderHint(QPainter::Antialiasing);        //防止图形走样
    ui->verticalLayout->addWidget(drawview1);//将图像放入布局中
}

TandRH::~TandRH()
{
    delete ui;
}
void TandRH::temperature_init()
{
    connect(ui->pushSendMaxY,&QPushButton::clicked,this,&TandRH::Set_MaxY_Range);
    connect(ui->pushSendMinY,&QPushButton::clicked,this,&TandRH::Set_MinY_Range);
    connect(ui->pushSendMaxX,&QPushButton::clicked,this,&TandRH::Set_MaxX_Range);
    connect(ui->pushSendMinX,&QPushButton::clicked,this,&TandRH::Set_MinX_Range);
}

void TandRH::draw_begin(){

timer2 = new QTimer;
timer2->start(1000);//TIME_CYCms采集一次
openflag = 1;
    qDebug() <<"start:time1";
    series1[0] = new QLineSeries;
     array_graph1 = new std::thread(idle_thread1);//创建空闲线程

     array_graph1->join();
 connect(timer2, SIGNAL(timeout()), this, SLOT(Draw_Graph1()));//连接定时器
    qDebug() <<"start:time2";
}
void TandRH::Draw_Graph1()
{
    qDebug() <<"start:time3";
    delete array_graph1;
 //   series2[1] = new QLineSeries;
  qDebug() <<"start:time7";
    delete series1[0];
        qDebug() <<"start:time8";
    series1[0] = new QLineSeries;
         qDebug() <<"start:time6";
    array_graph1 = new std::thread(&TandRH::draw_thread1, this);//创建画图线程
         qDebug() <<"start:time5";
    array_graph1->join();
 qDebug() <<"start:time4";
    drawing1->addSeries(series1[0]);
    drawing1->setAxisX(axisX1, series1[0]);
    drawing1->setAxisY(axisY1, series1[0]);

}
/*************功能：坐标轴手动设置**********************/
void TandRH::Set_MaxY_Range()
{

        if(!ui->linemaxY->text().isEmpty())//设置内容不能为空
        {
            axisY_max = ui->linemaxY->text().toInt();//将文本框中内容转换为int数据
            axisY1->setRange(axisY_min, axisY_max);//设置范围
        }

}
/*************功能：坐标轴手动设置**********************/
void TandRH::Set_MinY_Range()
{

        if(!ui->lineminY->text().isEmpty())
        {
            axisY_min = ui->lineminY->text().toInt();
            axisY1->setRange(axisY_min, axisY_max);
        }
}
/*************功能：坐标轴手动设置**********************/
void TandRH::Set_MaxX_Range()
{

        if(!ui->linemaxX->text().isEmpty())//设置内容不能为空
        {
            axisX_max = ui->linemaxX->text().toInt();//将文本框中内容转换为int数据
            axisX1->setRange(-axisX_max, -axisX_min);//设置范围
        }

}
/*************功能：坐标轴手动设置**********************/
void TandRH::Set_MinX_Range()
{

        if(!ui->lineminX->text().isEmpty())
        {
            axisX_min = ui->lineminX->text().toInt();
            axisX1->setRange(-axisX_max, -axisX_min);//设置范围
        }
}
