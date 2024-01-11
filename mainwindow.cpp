#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xlsxdocument.h"
#include <dialog_timein.h>
#include <math.h>
#include "tandrh.h"
#include "ui_tandrh.h"
#include "humidity.h"
#include "ui_humidity.h"
using namespace std;

QByteArray buffer;
QString currentCOM = "";

static int drawcnt = 0;
static int time_init = 0, time_end = 50;
static int axisY_max,axisY_min;
static int Started = 0;//标志是否已开始采集
static double max_range[17] = {0};
static double min_range[17];
static double lvbo[ARRAY][10] = {0};
QString fileName;
QXlsx::Document xlsx;
static int saveflag = 0,savenum = 0;
static int row_num,last_row_name;
//设置数据信息
static vector<vector<float>> array_signal;//二维数组
static vector<vector<float>> orginal_signal;//二维数组
vector<float> Temperature_signal;//温度数组
vector<float> RH_signal;//湿度数组
static vector<float> array_time;    //时间数组
static vector<int> array_cnt_save;                  //计数数组
static int index = -1;
int dp[17] = {0};
uint DATA_LEN = 8;
//static QByteArray buffer;
static QListView* RT_list[ARRAY+2];
static QStringList text_content[ARRAY+2];//记录文本的变量
static QStringListModel *model_text[ARRAY+2];
static QColor Graph_color[ARRAY] = {
                         QColor(255, 0, 0),//大红
                         QColor(0, 255, 0),//黑色
                         QColor(0, 0, 255),//Cyan
                         QColor(255, 0, 255),//MediumSeaGreen
                         QColor(255, 125, 0),//goldenrod
                         QColor(0, 255, 255),//SandyBrown
                         QColor(0, 0, 0),//DarkSeaGreen3
                         QColor(125, 125, 0),//Gold2
                       };


static thread* array_graph[THREAD_NUM];

//线程同步所需的信号量
std::mutex bMutex;//互斥锁，防止添加数据或显示数据的时候被打断
 int reading = 0;
int Proportion = 1;
/************************************************画图线程函数**********************************************/
//每个线程画step条曲线
void MainWindow::draw_thread(int start, int end) {
    if(index<1) return;
   //   qDebug() << "begin draw1";
    while(reading);//等待读结束
//qDebug() << "begin draw2";
    for(int num = start; num <= end; num++) {
        //series[num]->setPen(QPen(Graph_color[num], 1, Qt::SolidLine));  // 设置折线显示效果
        Series_display();//勾选通道
        if(dp[1] == 0)  series[0]->setPen(QColor(0,0,0,0));//通道隐藏
        if(dp[2] == 0)  series[1]->setPen(QColor(0,0,0,0));
        if(dp[3] == 0)  series[2]->setPen(QColor(0,0,0,0));
        if(dp[4] == 0)  series[3]->setPen(QColor(0,0,0,0));
        if(dp[5] == 0)  series[4]->setPen(QColor(0,0,0,0));
        if(dp[6] == 0)  series[5]->setPen(QColor(0,0,0,0));
        if(dp[7] == 0)  series[6]->setPen(QColor(0,0,0,0));
        if(dp[8] == 0)  series[7]->setPen(QColor(0,0,0,0));

        for (int i = 0; i <= time_end; i++)
        {
            series[num]->append(-i, array_signal[num][i]);
        }
        QString s = QString::number(round(array_signal[num][0]),'f',0);
        text_content[num].clear();
        text_content[num] << s;//显示到listview
    }
    if(end>6)
    {
    QString s = QString::number((Temperature_signal[0]),'f',2);
    text_content[8].clear();
    text_content[8] << s;//显示到listview
    s = QString::number((RH_signal[0]),'f',2);
    text_content[9].clear();
    text_content[9] << s;//显示到listview
    }
 // qDebug() << "end draw";
    return;
}

void idle_thread() {
    //空线程函数
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //串口初始化
    sys_init();
    //定时扫描和更新串口
    timer = new QTimer;
    connect(timer,&QTimer::timeout,this,&MainWindow::showValidPort);//实时更新端口号
    timer->start(1000); //每1000ms定时检测串口状态

    JSTimer = new QTimer;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) //扫描可用串口
    portStringList += info.portName();
    ui->comboVolt1->addItems(portStringList);

    orginal_signal.resize(ARRAY, vector<float>(BUFFERSIZE));
    array_signal.resize(ARRAY, vector<float>(BUFFERSIZE));
    array_time.resize(BUFFERSIZE);
    RH_signal.resize(BUFFERSIZE);
    Temperature_signal.resize(BUFFERSIZE);
    //设置listview关联
        RT_list[0] = ui->list_ch1;
        RT_list[1] = ui->list_ch2;
        RT_list[2] = ui->list_ch3;
        RT_list[3] = ui->list_ch4;
        RT_list[4] = ui->list_ch5;
        RT_list[5] = ui->list_ch6;
        RT_list[6] = ui->list_ch7;
        RT_list[7] = ui->list_ch8;
        RT_list[8] = ui->Temperature;
        RT_list[9] = ui->list_RH;

    for (int i = 0; i < ARRAY; i++)
        model_text[i] = new QStringListModel(text_content[i]);
    model_text[8] = new QStringListModel(text_content[8]);
    model_text[9] = new QStringListModel(text_content[9]);
    for (int i = 0; i < ARRAY; i++)
        series[i] = new QLineSeries;
    for(int i = 0;i<ARRAY;i++)
        min_range[i] = 1000000;

   ui->checkBox->setStyleSheet("QCheckBox{color:rgb(255, 0, 0)}");
   ui->checkBox_2->setStyleSheet("QCheckBox{color:rgb(0, 255, 0)}");
   ui->checkBox_3->setStyleSheet("QCheckBox{color:rgb(0, 0, 255)}");
   ui->checkBox_4->setStyleSheet("QCheckBox{color:rgb(255, 0, 255)}");
   ui->checkBox_5->setStyleSheet("QCheckBox{color:rgb(255, 125, 0)}");
   ui->checkBox_6->setStyleSheet("QCheckBox{color:rgb(0, 255, 255)}");
   ui->checkBox_7->setStyleSheet("QCheckBox{color:rgb(0, 0, 0)}");
   ui->checkBox_8->setStyleSheet("QCheckBox{color:rgb(125, 125, 0)}");
    /*****************设置标题和图标***********************/
    setWindowTitle(u8"8通道电阻采集");
    /**********************新建子窗口************************/
     TRH= new TandRH(this);
    TRH->close();
    RH= new Humidity(this);
   RH->close();
    /***********************画图*****************************/

    drawing = new QChart;
    drawing->setTitle(u8"传感器实时曲线");
    drawview = new QChartView(drawing);
    axisX = new QValueAxis;
    axisY = new QValueAxis;
    //建立数据源队列

    //建立坐标轴
    QBrush AxisColor;
    AxisColor.setColor(Qt::black);
    axisX->setRange(-time_end, time_init);                // 设置范围
    axisX->setLabelFormat("%d");                            // 设置刻度的格式
    axisX->setGridLineVisible(true);                        // 网格线可见
    axisX->setTickCount(6);                                 // 设置多少个大格
    axisX->setMinorTickCount(1);                            // 设置每个大格里面小刻度线的数目
    axisX->setTitleText(u8"time(0.5s)");                             // 设置描述

    axisY->setRange(0, 1000);
    axisY->setLabelFormat("%.1f");
    axisY->setGridLineVisible(true);
    axisY->setTickCount(8);
    axisY->setMinorTickCount(1);
    axisY->setTitleText(u8"data/KΩ");

    //为曲线添加坐标轴
    drawing->addAxis(axisX, Qt::AlignBottom);               // 下：Qt::AlignBottom  上：Qt::AlignTop
    drawing->addAxis(axisY, Qt::AlignLeft);                 // 左：Qt::AlignLeft    右：Qt::AlignRight
    drawing->legend()->setAlignment(Qt::AlignTop);
    drawing->legend()->setVisible(false);
    drawview->setRenderHint(QPainter::Antialiasing);        //防止图形走样
    ui->verticalLayout_5->addWidget(drawview);//将图像放入布局中
}

MainWindow::~MainWindow()
{
    delete ui;
}
// 重写closeEvent: 确认退出对话框
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton button;
    button=QMessageBox::question(this,tr("退出程序"),QString(tr("确认退出程序")),QMessageBox::Yes|QMessageBox::No);
    if(button==QMessageBox::No)
    {
        event->ignore(); // 忽略退出信号，程序继续进行
    }
    else if(button==QMessageBox::Yes)
    {
        event->accept(); // 接受退出信号，程序退出
    }
}
/*************功能：串口初始化**********************/
void MainWindow::sys_init()
{
    // port config
    global_port.setBaudRate(QSerialPort::Baud115200);  //波特率
    global_port.setParity(QSerialPort::NoParity)  ;   //无奇偶校验
    global_port.setDataBits(QSerialPort::Data8);    //8位数据位
    global_port.setStopBits(QSerialPort::OneStop);  // 1位停止位
    //connect
    //信号发出者地址-发什么信号-在那个类触发（地址）-槽函数
    connect(ui->pushOpen,&QPushButton::clicked,this,&MainWindow::my_btn_open_clicked);
    connect(ui->pushClose,&QPushButton::clicked,this,&MainWindow::my_btn_close_clicked);
    connect(ui->pushStart,&QPushButton::clicked,this,&MainWindow::my_btn_begin_clicked);
    connect(ui->pushStop,&QPushButton::clicked,this,&MainWindow::my_btn_stop_clicked);
    connect(ui->pushClear,&QPushButton::clicked,this,&MainWindow::Clear_data);
   // connect(ui->push_view, SIGNAL(clicked()), this, SLOT(Time_input()));
    connect(ui->push_view,&QPushButton::clicked,this,&MainWindow::ViewT);
     connect(ui->push_view_2,&QPushButton::clicked,this,&MainWindow::ViewRH);
    connect(&global_port,&QSerialPort::readyRead,this,&MainWindow::receive_data);
    connect(ui->checkBox_17,SIGNAL(clicked()),this,SLOT(Choose_Channel1_5()));
    connect(ui->checkBox_18,SIGNAL(clicked()),this,SLOT(Choose_Channel6_10()));
    connect(ui->action_excel, SIGNAL(triggered()), this, SLOT(save_excel()));
 //   connect(ui->pushVolt,&QPushButton::clicked,this,&MainWindow::Send_Temperature);
    connect(ui->pushSendMax,&QPushButton::clicked,this,&MainWindow::Set_Max_Range);
    connect(ui->pushSendMin,&QPushButton::clicked,this,&MainWindow::Set_Min_Range);
    connect(ui->pushSendMin_2,&QPushButton::clicked,this,&MainWindow::Set_X_Range);
}
/*******************************************槽函数************************************************/
//使用默认槽函数会出现点击一次响应两次
/*************功能：打开串口**********************/
void MainWindow::my_btn_open_clicked()
{
    /*-------------port_name-----------------*/
    if(global_port.isOpen())
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("Serial port has opened!"));
        QTimer::singleShot(500,m_box,SLOT(accept()));
        m_box->exec();
    }
    else
    {
        qDebug() <<ui->comboVolt1->currentText();
        global_port.setPortName(ui->comboVolt1->currentText());//设置端口号
        //global_port.setPortName("ttyAMA0");
        if(global_port.open(QIODevice::ReadWrite))//打开串口函数，会返回一个bool值判断是否打开
        {
            QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("message"),QString("Open!"));//弹出提示
            QTimer::singleShot(500,m_box,SLOT(accept()));//定时500ms显示后，关闭弹窗
            m_box->exec();
        }else
        {
            QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("Failed to open the serial port"));
            QTimer::singleShot(500,m_box,SLOT(accept()));
            m_box->exec();
        }
    }


}

void MainWindow::ViewT()
{
   // qDebug() << "showT";
    if(Started)
    {
         // bMutex.unlock();
          TRH->draw_begin();
    }

    TRH->show();

}

void MainWindow::ViewRH()
{
   // qDebug() << "showRH";
    if(Started)
    {
          RH->drawRH_begin();
        //  bMutex.unlock();
    }

    RH->show();

}
/*************功能：关闭串口**********************/
void MainWindow::my_btn_close_clicked()
{
    if(Started == 0)
    {
     //   qDebug() << "close";
        global_port.close();
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("Message"),QString("Closed"));
        QTimer::singleShot(500,m_box,SLOT(accept()));
        m_box->exec();
    }
   else
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("Collecting!"));
        QTimer::singleShot(500,m_box,SLOT(accept()));
        m_box->exec();
    }

}
/*************功能：开始采集**********************/
void MainWindow::my_btn_begin_clicked()
{
    if(global_port.isOpen())
    {
        if(saveflag == 0)
        {
        save_excel();
        }
        if(Started == 0)
        {

            QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("Success"),QString("START"));
            QTimer::singleShot(500,m_box,SLOT(accept()));
            m_box->exec();
            Started = 1;
            //设置采集定时器
          //  qDebug() <<"sart:";
            timer1 = new QTimer;
            timer1->start(TIME_CYC);//TIME_CYCms采集一次
          //  qDebug() <<"sart:";
            for (int j = 0; j < THREAD_NUM; j++)//THREAD_NUM采集线程数
                 array_graph[j] = new std::thread(idle_thread);//创建空闲线程
            for (int j = 0; j < THREAD_NUM; j++)
                 array_graph[j]->join();
            connect(timer1, SIGNAL(timeout()), this, SLOT(Draw_Graph()));//连接定时器
            //获取当前时间给计时器
            JSTime = JSTime.currentTime();
            JSTimer->start(100);

        }
        else
        {
            QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("Collecting!"));
            QTimer::singleShot(1000,m_box,SLOT(accept()));
            m_box->exec();
        }

    }
    else
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("please open the port"));
        QTimer::singleShot(1000,m_box,SLOT(accept()));
        m_box->exec();
    }
}
/*************功能：停止采集**********************/
void MainWindow::my_btn_stop_clicked()
{
    if(global_port.isOpen())
    {
    if(Started == 1)
    {
        Started = 0;
        for (int j = 0; j < THREAD_NUM; j++)
        {
            delete array_graph[j];//删除线程
        }
        timer1->stop();
        delete timer1;//删除采集线程
    JSTimer->stop();
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("Message"),QString("STOP"));
        QTimer::singleShot(500,m_box,SLOT(accept()));
        m_box->exec();
    }
    else
    {
//        QMessageBox::warning(this, "error", u8"没有开始采集！");
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("Did not start Collecting!"));
        QTimer::singleShot(500,m_box,SLOT(accept()));
        m_box->exec();
    }
    }
    else
    {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("Did not open the seriport"));
        QTimer::singleShot(500,m_box,SLOT(accept()));
        m_box->exec();
    }
}
/*************功能：接受数据**********************/
void MainWindow::receive_data()
{
    reading = 1;
    bool is_readall = false;
    QByteArray array = global_port.readAll();
    int x;
    bool ok = 1;
    int start;
    uint sum = 0;
    uint checksum = 0;
 //    qDebug() << "begin receive";
    if(Started == 1)
    {
        if((!array.contains("{"))&&buffer.isNull())//异常：头部丢失
        {
           // qDebug() <<"1:";
             reading = 0;
            return ;
        }
        //第一种，有头无尾，附加
        if(array.contains("{")&&(!array.contains("}")))
        {
          //   qDebug() <<"2:";
           // buffer.clear();
              reading = 0;
            buffer.append(array);
        }
        //第二种：无头无尾且变量已有内容，数据中段部分，继续附加即可
        if((!array.contains("{"))&&(!array.contains("}"))&&(!buffer.isNull()))
        {
           //  qDebug() <<"3:";
              reading = 0;
            buffer.append(array);
        }
        //第三种：无头有尾且变量已有内容，已完整读取,附加后可做处理
        if((!array.contains("{"))&&(array.contains("}"))&&(!buffer.isNull()))
        {
           //  qDebug() <<"4:";
             buffer.append(array);
             if(buffer.size()==40)
             is_readall = true;
        }
        //第四种：有头有尾（一段完整的内容），已完整读取
        if((array.contains("{"))&&(array.contains("}")))
        {
            // qDebug() <<"5:";
             buffer.append(array);
             if(buffer.size()==40)
             is_readall = true;
        }
        if(is_readall)//缓存区有头有尾，已完整读取
        {

           // qDebug() <<"buffer_size:";
            qDebug() <<buffer.size();//输出长度


            for(int i = 0;i<buffer.size();i++)
            {
                if((uint(uint(buffer.at(i))&0xff))==123)//定位帧头
                {
                    start = i+1;
                   qDebug() <<"start:"<<i<<endl;
                    break;
                }
            }
            DATA_LEN = ((uint)(buffer.at(start)))&0xff ;//帧头后接通道数
            qDebug() <<DATA_LEN;
            if(DATA_LEN==ARRAY&&(uint)(buffer.at(buffer.size()-1))== 125)
            {
            start++;
            //读取当时时间
            QTime currTime = QTime::currentTime();
            int t = JSTime.msecsTo(currTime);
            QTime showTime(0,0,0,0);
            showTime = showTime.addMSecs(t);
            if (index < BUFFERSIZE) index++;
            for(int i = 0;i<DATA_LEN;i++)//接收通道数后跟的数据
            {
                if (index >= BUFFERSIZE)  array_signal.at(i).pop_back();
                uint buf_0 = ((uint)buffer.at(4 * i+start)<< 24)& 0xff000000;
                uint buf_1 = ((uint)(buffer.at(4 * i + 1+start)) << 16)& 0x00ff0000;
                uint buf_2 = ((uint)(buffer.at(4 * i + 2+start)) << 8)  & 0x0000ff00;
                uint buf_3 = ((uint)(buffer.at(4 * i + 3+start)) )&0x000000ff ;
                float buf = buf_0 + buf_1 + buf_2 + buf_3;
                sum+=buf_3;//校验和
//                if(index<10)
//                {

//                    lvbo[i][index] = buf;
//                    buf = 0;
//                    for(int k = 0;k<index;k++)
//                    {
//                       buf += lvbo[i][k];
//                    }
//                    buf = buf/index;
//                    qDebug() <<"index:"<<index;
//                    qDebug() <<"buf:"<<buf;

//                }
//                else
//                {
//                    for(int k = 0;k<9;k++)
//                    {
//                        lvbo[i][k] = lvbo[i][k+1];
//                    }
//                    lvbo[i][9] = buf;
//                    buf = 0;
//                    for(int k = 0;k<10;k++)
//                    {
//                        buf += lvbo[i][k];
//                    }
//                    buf = buf / 10.0;
//                }

                orginal_signal.at(i).insert(orginal_signal.at(i).begin(),
                    (float)(buf));//
                    buf = buf/1000.0;
                    if(buf<0) buf = 0;
                array_signal.at(i).insert(array_signal.at(i).begin(),
                    (float)(buf));//
                if(max_range[i]<buf) max_range[i] = buf;
                if(min_range[i]>buf) min_range[i] = buf;
                qDebug() <<buf;
            }
            //  qDebug() <<"checkcum 1!";
            uint buf_0 = ((uint)(buffer.at(4 * DATA_LEN + start)) << 8)  & 0x0000ff00;
            uint buf_1 = ((uint)(buffer.at(4 * DATA_LEN + 1 +start)) )&0x000000ff ;
            uint buf =  buf_0 + buf_1;
            Temperature_signal.insert(Temperature_signal.begin(),(float)(buf/10.0));
           //  qDebug() <<"checkcum 2!";
            uint buf_2 = ((uint)(buffer.at(4 * DATA_LEN + 2 + start)) << 8)  & 0x0000ff00;
            uint buf_3 = ((uint)(buffer.at(4 * DATA_LEN + 3 +start)) )&0x000000ff ;
            buf =  buf_2 + buf_3;
            RH_signal.insert(RH_signal.begin(),(float)(buf/10.0));

            QString str_htime = showTime.toString("hh");
            QString str_mtime = showTime.toString("mm");
            QString str_stime = showTime.toString("ss.zzz");
            float flo_htime = str_htime.toFloat();
            float flo_mtime = str_mtime.toFloat();
            float flo_stime = str_stime.toFloat();
            float flo_time =flo_htime*3600+ flo_mtime*60+flo_stime;
        //    qDebug() << "time: " << flo_time << endl;
            array_time.insert(array_time.begin(), flo_time);


             savenum++;
            if(savenum>=TIME10&&saveflag==1)
            {
                save();
                savenum = 0;
            }
            sum = sum&0xff;
            checksum = (uint)(buffer.at(buffer.size()-2))&0xff;//检查校验位
           // qDebug() <<"checkcum 3!";
            if(checksum == sum)
            {
               // qDebug() <<"checkcum successful!";
            }
            else
            {
               //  qDebug()<<checksum;
               // qDebug() <<"checkcum failed!";
            }
            if((uint)(buffer.at(buffer.size()-1))== 125)//帧尾
            {
              // qDebug() <<"end!";
            }
            buffer.clear();
             is_readall = false;
            reading = 0;
            }
            else
                {
                  //  qDebug() <<"end error";
               // qDebug() <<uint(buffer.at(buffer.size()-1)&0xff);
               buffer.clear();
               is_readall = false;
                reading = 0;
               }
        }

    }
    else
    {
 reading = 0;
    }
}
/*************功能：坐标轴手动设置**********************/
void MainWindow::Set_Max_Range()
{
    if(ui->checkBox_autoset->isChecked())//自动设置被选中
    {
        //do nothing
    }
    else
    {
        if(!ui->linemax->text().isEmpty())//设置内容不能为空
        {
            axisY_max = ui->linemax->text().toInt();//将文本框中内容转换为int数据
            axisY->setRange(axisY_min, axisY_max);//设置范围
        }
    }
}
/*************功能：坐标轴手动设置**********************/
void MainWindow::Set_Min_Range()
{
    if(ui->checkBox_autoset->isChecked())
    {
        //do nothing
    }
    else
    {
        if(!ui->linemin->text().isEmpty())
        {
            axisY_min = ui->linemin->text().toInt();
            axisY->setRange(axisY_min, axisY_max);
        }
    }
}
/*************功能：坐标轴手动设置**********************/
void MainWindow::Set_X_Range()
{
    if(!ui->linemintime->text().isEmpty())
    {
        time_end = ui->linemintime->text().toInt();
        axisX->setRange(-time_end, 0);
    }
}
/*************功能：坐标轴自动设置**********************/
void MainWindow::Auto_Set_Range()
{
    int max = 0,min = 1000000;
    int setflag = 0;
    if(ui->checkBox_autoset->isChecked())
    {
        for(int i = 0;i<ARRAY;i++)
        {
            if(dp[i+1]==1)
            {
                setflag = 1;
                if(max<max_range[i]) max = max_range[i];
                if(min>min_range[i]) min = min_range[i];
            }
        }
        if(setflag&&max>min)
        {
            axisY_max = max;
            axisY_min = min;
            axisY->setRange(axisY_min, axisY_max);
        }
    }
    else
    {
        //do nothing
    }
}
/*************功能：显示可用串口**********************/
void MainWindow::showValidPort()
{
    QStringList newPortStringList;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        newPortStringList += info.portName();
    if(newPortStringList.size() != portStringList.size())
    {
        portStringList = newPortStringList;
        ui->comboVolt1->clear();
        ui->comboVolt1->addItems(portStringList);
    }
    if(currentCOM != ui->comboVolt1->currentText()) //串口突然断开连接了
    {
        currentCOM = ui->comboVolt1->currentText();

    }
}

////*************功能：发送控温******/
//void MainWindow::Send_Temperature()
//{
//    if(global_port.isOpen())
//    {
//    //qDebug() <<"Send_Temperature:";
//    voltdata[0] =   ui->comboBox->currentIndex();
//    voltdata[1] =   ui->comboBox_2->currentIndex();
//    voltdata[2] = 0x0d;
//    voltdata[3] = 0x0a;
//    global_port.write(voltdata,4);
//    QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("message"),QString("Successful!"));
//    QTimer::singleShot(500,m_box,SLOT(accept()));
//    m_box->exec();
//    }
//    else
//    {
//        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("please open the port"));
//        QTimer::singleShot(500,m_box,SLOT(accept()));
//        m_box->exec();
//    }
//}
//*************功能：画图（定时器）并显示实时数据******/
//*开二个线程画*/
void MainWindow::Draw_Graph()
{
    if(time_end>1800)
    {
        drawcnt++;
        if(drawcnt >50)
        {
            drawcnt = 0;
        }
        else
        {
            return ;
        }
    }
    else
    {
        drawcnt = 0;
    }
    int j = 0;
    Auto_Set_Range();

    for (j = 0; j < ARRAY; j++)
    {
    delete model_text[j];
    model_text[j] = new QStringListModel(text_content[j]);
    model_text[j]->setStringList(text_content[j]);
    RT_list[j]->setModel(model_text[j]);
    }
    delete model_text[8];
    model_text[8] = new QStringListModel(text_content[8]);
    model_text[8]->setStringList(text_content[8]);
    RT_list[8]->setModel(model_text[8]);

    delete model_text[9];
    model_text[9] = new QStringListModel(text_content[9]);
    model_text[9]->setStringList(text_content[9]);
    RT_list[9]->setModel(model_text[9]);

    for (j = 0; j < ARRAY; j++) {
        delete series[j];
        series[j] = new QLineSeries;
        series[j]->setPen(QPen(Graph_color[j], 1, Qt::SolidLine));  // 设置折线显示效果
    }

    //目前只开2个线程，共8条曲线
    for (j = 0; j < THREAD_NUM; j++)
       delete array_graph[j];
    for (j = 0; j < THREAD_NUM; j++) {
        array_graph[j] = new std::thread(&MainWindow::draw_thread, this, j*ARRAY/THREAD_NUM, (j+1)*ARRAY / THREAD_NUM - 1);//创建画图线程
    }

    for (j = 0; j < THREAD_NUM; j++)
     array_graph[j]->join();
    for (j = 0; j < ARRAY; j++)
    {
     drawing->addSeries(series[j]);
     drawing->setAxisX(axisX, series[j]);
     drawing->setAxisY(axisY, series[j]);
    }
     //   qDebug() <<"end error8";
}
/*************功能：清空数据区和曲线******************/
//只有在不采集的情况下才能清空
//不仅清空显示，缓存里已有的数据也会清空
void MainWindow::Clear_data()
{
    if (Started) {
        QMessageBox *m_box = new QMessageBox(QMessageBox::Information,QString("error"),QString("Collecting!"));
        QTimer::singleShot(500,m_box,SLOT(accept()));
        m_box->exec();
    }
    else {
        for (int i = 0; i < ARRAY; i++)
        {
            text_content[i].clear();
            series[i]->clear();
        }
        index = -1;
        row_num = -1;
        last_row_name = 0;
        array_signal.clear();
        orginal_signal.clear();
        array_signal.resize(ARRAY, vector<float>(BUFFERSIZE));
        orginal_signal.resize(ARRAY, vector<float>(BUFFERSIZE));
        saveflag = 0;
        RH_signal.clear();
        Temperature_signal.clear();
        RH_signal.resize(BUFFERSIZE);
        Temperature_signal.resize(BUFFERSIZE);
    }
}
/*************功能：隐藏曲线**********************/
void MainWindow::Series_display()
{
    if(ui->checkBox_17->isChecked())
    {
        for(int i = 1;i<5;i++)
            dp[i] = 1;
    }
    else
    {
    if(ui->checkBox->isChecked())
        dp[1] = 1;
    else
        dp[1] = 0;
    if(ui->checkBox_2->isChecked())
        dp[2] = 1;
    else
        dp[2] = 0;
    if(ui->checkBox_3->isChecked())
        dp[3] = 1;
    else
        dp[3] = 0;
    if(ui->checkBox_4->isChecked())
        dp[4] = 1;
    else
        dp[4] = 0;
    if(ui->checkBox_5->isChecked())
        dp[5] = 1;
    else
        dp[5] = 0;
    }
    if(ui->checkBox_18->isChecked())
    {
        for(int i = 5;i<9;i++)
            dp[i] = 1;
    }
    else{

     if(ui->checkBox_5->isChecked())
            dp[5] = 1;
        else
            dp[5] = 0;
    if(ui->checkBox_6->isChecked())
        dp[6] = 1;
    else
        dp[6] = 0;
    if(ui->checkBox_7->isChecked())
        dp[7] = 1;
    else
        dp[7] = 0;
    if(ui->checkBox_8->isChecked())
        dp[8] = 1;
    else
        dp[8] = 0;

    }
}
/*************功能：隐藏曲线**********************/
void MainWindow::Choose_Channel1_5()
{
    if(ui->checkBox_17->isChecked())
    {
        ui->checkBox->setCheckState(Qt::Checked);
        ui->checkBox_2->setCheckState(Qt::Checked);
        ui->checkBox_3->setCheckState(Qt::Checked);
        ui->checkBox_4->setCheckState(Qt::Checked);


    }
    else
    {
        ui->checkBox->setCheckState(Qt::Unchecked);
        ui->checkBox_2->setCheckState(Qt::Unchecked);
        ui->checkBox_3->setCheckState(Qt::Unchecked);
        ui->checkBox_4->setCheckState(Qt::Unchecked);

    }

}
/*************功能：隐藏曲线**********************/
void MainWindow::Choose_Channel6_10()
{

     if(ui->checkBox_18->isChecked())
    {
        ui->checkBox_5->setCheckState(Qt::Checked);
        ui->checkBox_6->setCheckState(Qt::Checked);
        ui->checkBox_7->setCheckState(Qt::Checked);
        ui->checkBox_8->setCheckState(Qt::Checked);

    }
     else
     {
         ui->checkBox_5->setCheckState(Qt::Unchecked);
         ui->checkBox_6->setCheckState(Qt::Unchecked);
         ui->checkBox_7->setCheckState(Qt::Unchecked);
         ui->checkBox_8->setCheckState(Qt::Unchecked);

     }
}
///*************功能：数据保存成excel*******************/
//void MainWindow::save_excel()
//{
//    //行数列数
//    int row_num = index;


//    QXlsx::Document xlsx;
//    xlsx.write("A1", u8"通道一(Ω)"); xlsx.write("B1", u8"通道二(Ω)"); xlsx.write("C1", u8"通道三(Ω)");
//    xlsx.write("D1", u8"通道四(Ω)"); xlsx.write("E1", u8"通道五(Ω)"); xlsx.write("F1", u8"通道六(Ω)");
//    xlsx.write("G1", u8"通道七(Ω)"); xlsx.write("H1", u8"通道八(Ω)"); xlsx.write("I1", u8"温度(℃)");
//    xlsx.write("J1", u8"湿度(%)");

//    for (int i = 0; i <= row_num; i++) {
//        for(int j = 0; j< ARRAY; j++)
//            xlsx.write(i + 2, j + 1, orginal_signal[j][i]);
//        xlsx.write(i + 2, 9, Temperature_signal[i]);
//        xlsx.write(i + 2, 10, RH_signal[i]);//row col
//    }
//    QString fileName = QFileDialog::getSaveFileName(this, "Save",
//        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
//        "Excel files(*.xlsx *.xls)");
//    xlsx.saveAs(QDir::toNativeSeparators(fileName));
//}
/*************功能：数据保存成excel*******************/
void MainWindow::save_excel()
{

    index = -1;
    row_num = -1;
    last_row_name = 0;
        xlsx.write("A1", u8"通道一(Ω)"); xlsx.write("B1", u8"通道二(Ω)"); xlsx.write("C1", u8"通道三(Ω)");
        xlsx.write("D1", u8"通道四(Ω)"); xlsx.write("E1", u8"通道五(Ω)"); xlsx.write("F1", u8"通道六(Ω)");
        xlsx.write("G1", u8"通道七(Ω)"); xlsx.write("H1", u8"通道八(Ω)"); xlsx.write("I1", u8"温度(℃)");
        xlsx.write("J1", u8"湿度(%)");xlsx.write("K1", u8"时间（s）");

    fileName = QFileDialog::getSaveFileName(this, "Save",
        QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
        "Excel files(*.xlsx *.xls)");
    xlsx.saveAs(QDir::toNativeSeparators(fileName));
    saveflag = 1;
}
void MainWindow::save()
{
    //行数列数
    last_row_name = row_num+1;
    row_num = index;
   // qDebug() <<"end error9";

    QXlsx::Document xlsx(fileName);

    for (int i = last_row_name; i <= row_num; i++) {
        for(int j = 0; j< ARRAY; j++)
            xlsx.write(i + 2, j + 1, orginal_signal[j][row_num-i]);
        xlsx.write(i + 2, 9, Temperature_signal[row_num-i]);
        xlsx.write(i + 2, 10, RH_signal[row_num-i]);//row col
        xlsx.write(i + 2, 11, array_time[row_num-i]);//row col
    }
    xlsx.save();
  //  qDebug() <<"end error10";
}
