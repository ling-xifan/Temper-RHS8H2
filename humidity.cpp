#include "humidity.h"
#include "ui_humidity.h"
#include "mainwindow.h"
using namespace std;

extern vector<float> RH_signal;//湿度数组
extern int reading;
extern std::mutex bMutex;//
static int openflag = 0;
static int axisY_max = 100,axisY_min = 50;
static int axisX_max = 500,axisX_min = 0;
static thread* array_graph2;
static QColor Graph_color[2] = {
                         QColor(255, 0, 0),//大红
                         QColor(0, 255, 0)
                       };
void idle_thread2() {
    //空线程函数
}
// 重写closeEvent: 确认退出对话框
void Humidity::closeEvent(QCloseEvent *event)
{
if(openflag)
{
       delete series2[1];
    delete array_graph2;//删除线程
    timer3->stop();
    delete timer3;//删除采集线程

}
 event->accept(); // 接受退出信号，程序退出
}
void Humidity::draw_thread2() {
   // qDebug() <<"start:drawRH";

   while(reading);//等待读结束
  // bMutex.lock();
        series2[1]->setPen(QPen(Graph_color[1], 3, Qt::SolidLine));// 设置折线显示效果
        for (int i = 0; i <= axisX_max; i++)
            series2[1]->append(-i, RH_signal[i]);
         //   qDebug() <<"end";
     //   bMutex.unlock();
   return;
}


Humidity::Humidity(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Humidity)
{
    ui->setupUi(this);
    Humidity_init();

    /*****************设置标题和图标***********************/
    setWindowTitle(u8"Humidity");

    drawing2 = new QChart;
    drawing2->setTitle(u8"Humidity");
    drawview2 = new QChartView(drawing2);
    axisX2 = new QValueAxis;
    axisY2 = new QValueAxis;
    //建立数据源队列

    //建立坐标轴
    QBrush AxisColor1;
    AxisColor1.setColor(Qt::black);
    axisX2->setRange(-500, 0);                // 设置范围
    axisX2->setLabelFormat("%d");                            // 设置刻度的格式
    axisX2->setGridLineVisible(true);                        // 网格线可见
    axisX2->setTickCount(6);                                 // 设置多少个大格
    axisX2->setMinorTickCount(1);                            // 设置每个大格里面小刻度线的数目
    axisX2->setTitleText(u8"time");                             // 设置描述

    axisY2->setRange(50, 100);
    axisY2->setLabelFormat("%.1f");
    axisY2->setGridLineVisible(true);
    axisY2->setTickCount(8);
    axisY2->setMinorTickCount(1);
    axisY2->setTitleText(u8"RH/%");

    //为曲线添加坐标轴
    drawing2->addAxis(axisX2, Qt::AlignBottom);               // 下：Qt::AlignBottom  上：Qt::AlignTop
    drawing2->addAxis(axisY2, Qt::AlignLeft);                 // 左：Qt::AlignLeft    右：Qt::AlignRight
    drawing2->legend()->setAlignment(Qt::AlignTop);
    drawing2->legend()->setVisible(false);
    drawview2->setRenderHint(QPainter::Antialiasing);        //防止图形走样
    ui->verticalLayout_2->addWidget(drawview2);//将图像放入布局中
}

Humidity::~Humidity()
{
    delete ui;
}
void Humidity::Humidity_init()
{
    connect(ui->pushSendMaxY,&QPushButton::clicked,this,&Humidity::Set_MaxY_Range);
    connect(ui->pushSendMinY,&QPushButton::clicked,this,&Humidity::Set_MinY_Range);
    connect(ui->pushSendMaxX,&QPushButton::clicked,this,&Humidity::Set_MaxX_Range);
    connect(ui->pushSendMinX,&QPushButton::clicked,this,&Humidity::Set_MinX_Range);
}

void Humidity::drawRH_begin(){
   // qDebug() <<"start:time";
timer3 = new QTimer;
timer3->start(1000);//TIME_CYCms采集一次
openflag = 1;
series2[1] = new QLineSeries;
     array_graph2= new std::thread(idle_thread2);//创建空闲线程
    array_graph2->join();
 connect(timer3, SIGNAL(timeout()), this, SLOT(Draw_Graph2()));//连接定时器
    // qDebug() <<"start:time1";
}
void Humidity::Draw_Graph2()
{
      //  qDebug() <<"start:time3";
        delete array_graph2;
     //   series2[1] = new QLineSeries;
     // qDebug() <<"start:time7";
        delete series2[1];
           // qDebug() <<"start:time8";
        series2[1] = new QLineSeries;
             //qDebug() <<"start:time6";
        array_graph2 = new std::thread(&Humidity::draw_thread2, this);//创建画图线程
          //   qDebug() <<"start:time5";
        array_graph2->join();
    // qDebug() <<"start:time4";
        drawing2->addSeries(series2[1]);
        drawing2->setAxisX(axisX2, series2[1]);
        drawing2->setAxisY(axisY2, series2[1]);

}
/*************功能：坐标轴手动设置**********************/
void Humidity::Set_MaxY_Range()
{

        if(!ui->linemaxY->text().isEmpty())//设置内容不能为空
        {
            axisY_max = ui->linemaxY->text().toInt();//将文本框中内容转换为int数据
            axisY2->setRange(axisY_min, axisY_max);//设置范围
        }

}
/*************功能：坐标轴手动设置**********************/
void Humidity::Set_MinY_Range()
{

        if(!ui->lineminY->text().isEmpty())
        {
            axisY_min = ui->lineminY->text().toInt();
            axisY2->setRange(axisY_min, axisY_max);
        }
}
/*************功能：坐标轴手动设置**********************/
void Humidity::Set_MaxX_Range()
{

        if(!ui->linemaxX->text().isEmpty())//设置内容不能为空
        {
            axisX_max = ui->linemaxX->text().toInt();//将文本框中内容转换为int数据
            axisX2->setRange(-axisX_max, -axisX_min);//设置范围
        }

}
/*************功能：坐标轴手动设置**********************/
void Humidity::Set_MinX_Range()
{

        if(!ui->lineminX->text().isEmpty())
        {
            axisX_min = ui->lineminX->text().toInt();
            axisX2->setRange(-axisX_max, -axisX_min);//设置范围
        }
}
