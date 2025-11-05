//
// Created by 20648 on 2023/7/21.
//

// You may need to build the project (run Qt uic code generator) to get "ui_rtspUI.h" resolved

#include "rtspui.h"
#include "ui_rtspUI.h"
#include <QDebug>
#include <QLabel>
#include <QListView>
#include <QMessageBox>
#include <algorithm>
#include <winsock2.h>
#include <sstream>
#include <iostream>
#include <QTime>
#include "./pushBtn/pushBtn.h"

//在label上创建一个label显示播放图片，通过定时器逐渐放大，逐渐透明
rtspUI::rtspUI(QWidget *parent) : QWidget(parent), ui(new Ui::rtspUI) {
    ui->setupUi(this);
    this->setGeometry(200, 200, 1920, 1080);
    this->setStyleSheet("QWidget#rtspUI {background-color:qlineargradient"
    "(spread : pad, x1 : 0, y1 : 0, x2 : 1, y2 : 1, stop:0 #101434, stop:0.5  #9a6673, stop:1 #e49694)}");
    this->setMouseTracking(true);
    widgets_init();/*部件初始化*/

    /*从数据库获取数据*/
    auto *sql = new mysql(this);
    urlMap = sql->transferSqlData();//获取数据库数据
    qDebug()<<urlMap;
    if (!urlMap.isEmpty())
        getMapData(urlMap);
    delete sql;

    /* 实例化 tcp 服务器与 tcp 套接字 */
    tcpSocket = new QTcpSocket(this);
    tcpServer = new QTcpServer(this);
    tcpListen();
    connect(tcpServer, SIGNAL(newConnection()),this, SLOT(tcpConnect()));

    my_videoLabel_list = new videoList(this);
    devnum = -1;

    qint64 processId = QCoreApplication::applicationPid(); //获取当前进程的PID
    qDebug()<<"rtspUI进程ID: " + QString::number(processId);

    this->show();
}

rtspUI::~rtspUI() {
    tcpStopConnect();
    if (AddUrl != nullptr)
        delete AddUrl;
    if (serialPortThraed != nullptr)
        delete serialPortThraed;
    delete ui;
}

/*rtspUI窗口部件初始化*/
void rtspUI::widgets_init(void)
{
    ui->hWidget->setStyleSheet("background:transparent");
    /*下拉列表*/
    //combobox下拉框样式表生效
    setComboBox();
    ui->comboBox->setView(new QListView());

//    myVideoScrollArea = new videoScrollArea(320,  frame_height * 2 + INTERVAL,this);
//    myVideoScrollArea->move((frame_width + INTERVAL) * 2 + 20, 100);
    mySwitchBtn = new SwitchBtn(100, 50, this);
    mySwitchBtn->move(640, 10);
    /*信号与槽*/
    connect(ui->pushButton, &QPushButton::clicked, this, &rtspUI::slotBtnClicked);
    connect(ui->comboBox, SIGNAL(currentTextChanged(QString)),
            this, SLOT(getComboBoxText(QString)));
    connect(mySwitchBtn, SIGNAL(sigClicked(bool)),this, SLOT(switchBtnClicked(bool)));
//    connect(myVideoScrollArea, SIGNAL(moveVideoLabel(int, int)),
//            this, SLOT(changeVideoLabelFromScrollArea(int, int)));
//    connect(myVideoScrollArea, SIGNAL(detaleVideoLabel(int)),
//            this, SLOT(deleteVideoLabelFromScrollArea(int)));
}

/*comboBox*/
void rtspUI::setComboBox(void) {
    //填充下拉选项
    ui->comboBox->clear();//清空combobox
    pItemModel = qobject_cast<QStandardItemModel*>(ui->comboBox->model());

    //字体设置
    int combobox_item_fontsize = 12;
    //font.setPixelSize(combobox_item_fontsize*scale);
    font.setPointSize(combobox_item_fontsize);
    font.setFamily("黑体");

    //填充默认项（在没有任何数据时，可以先做一个默认的提示项给用户，然后让用户自己输入）
    QString tip_string("请选择用户名");
    ui->comboBox->addItem(tip_string);
    pItemModel->item(0)->setIcon(QIcon("D:/3-MyProject/pull_the_video_stream/images/camera.png"));    //修改某项图标
    pItemModel->item(0)->setForeground(QColor(255, 0, 0));            //修改某项文本颜色
    pItemModel->item(0)->setBackground(QColor(220,220,220));    //修改某项背景颜色
    pItemModel->item(0)->setFont(font);
    pItemModel->item(0)->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter);    //修改某项文本对齐方式
}

/*给comboBox添加item*/
void rtspUI::addComboBoxItem(void)
{
    int i = 0;
    ui->comboBox->clear();//清空comboBox
    ui->comboBox->addItem("NONE");
    pItemModel->item(i)->setIcon(QIcon("D:/3-MyProject/pull_the_video_stream/images/camera.png")); //修改某项图标
    pItemModel->item(i)->setFont(font);
    pItemModel->item(i)->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter); //修改某项文本对齐方式
    i++;
    for(QMap<QString, QString>::iterator iter = urlMap.begin(); iter != urlMap.end(); iter++) {
        qDebug()<<"key:"<<iter.key()<<" value:"<<iter.value()<<endl;
        ui->comboBox->addItem(iter.key());
        pItemModel->item(i)->setIcon(QIcon("D:/3-MyProject/pull_the_video_stream/images/camera.png")); //修改某项图标
        pItemModel->item(i)->setFont(font);
        pItemModel->item(i)->setTextAlignment(Qt::AlignVCenter | Qt::AlignHCenter); //修改某项文本对齐方式

        //pItemModel->item(i)->setText("修改的文本  " + QString::number(i + 1));                          //修改某项文本
        //pItemModel->item(i)->setForeground(QColor(255, 0, 0));            //修改某项文本颜色
        // pItemModel->item(i)->setBackground(QColor(220,220,220));    //修改某项背景颜色（若样式表中已经设置了表项的背景颜色，则不会生效）
        i++;
    }
}

void rtspUI::videoPlay(QString devurl, QString devname, int dev, int scale)
{
    videoLabel *my_video;
    if (dev < 4) {
        my_videoLabel_list->append(dev, frame_width, frame_height, this);
        my_video = my_videoLabel_list->get(dev);
        my_video->move(20 + (frame_width + INTERVAL) * (dev % 2),
                       100 + (frame_height + INTERVAL) * (dev / 2));
        my_video->winIsLarge = true;
    } else {
        my_videoLabel_list->append(dev, frame_width_320, frame_height_240, this);
        my_video = my_videoLabel_list->get(dev);
        my_video->move((frame_width + INTERVAL) * 2 + 20,
                       100 + (frame_height + INTERVAL) * (dev - 4));
        my_video->magnifyBtn->setEnabled(false);
        my_video->winIsLarge = false;
    }
    //my_video[dev]->playBtn->setMouseTracking(true);
    connect(my_video, SIGNAL(deleteVideoLabel(int)),
            this, SLOT(deleteVideoLabelBtnClicked(int)));
    connect(my_video, SIGNAL(changeVideoLabel(int, int)),
            this, SLOT(changeVideoLabel(int, int)));
    my_video->set_url_name(devurl, devname);
    my_video->W_H_ratio = scale;
    my_video->show();
    my_video->setDevNum(dev);
}

bool rtspUI::getFullScreenFlag()
{
    for(int i = 0; i < alreadyCreatVideo; i++) {
        videoLabel *my_video = my_videoLabel_list->get(i);
        if(my_video->fullScreen)
            return true;
    }
    return false;
}

/*----------------------------some rtspUI slot functions----------------------------*/

/*按钮槽函数*/
void rtspUI::slotBtnClicked() {
    if (AddUrl == nullptr) {
        AddUrl = new addurl();
        connect(AddUrl, &addurl::alreadyGetData, this, &rtspUI::getMapData);
        // 由于 AddUrl 会在关闭时被自动删除 AddUrl置空
        connect(AddUrl, &QObject::destroyed, this, [this]() {
            AddUrl = nullptr; // 自动置空
        });
    } else {
        delete AddUrl;
        AddUrl = nullptr;
    }
    //connect(AddUrl, &addurl::deleteThis, this, &rtspUI::deleteAddurl);
}

/*开关按钮槽函数*/
void rtspUI::switchBtnClicked(bool status)
{
    if (status) {
        serialPortWin = new QWidget();
        serialPortWin->resize(150, 50);
        serialPortWin->setAttribute(Qt::WA_DeleteOnClose); //关闭按钮按下后，销毁该部件
        serialPortBox = new QComboBox(serialPortWin);
        serialPortBox->setGeometry(12, 5, 150, 40);
        /*查找可用串口*/
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
            serialPortBox->addItem(info.portName());
        }

        serialPortWin->show();
        connect(serialPortWin, SIGNAL(destroyed(QObject *)),
                this, SLOT(serialPortWinClose(QObject *)));

        char ps2_mode[] = "open";
        if(tcpSocket->state() == tcpSocket->ConnectedState) {
            tcpSocket->write(ps2_mode); // 写入数据块
        }
    } else   {
        char ps2_mode[] = "close";
        if(tcpSocket->state() == tcpSocket->ConnectedState) {
            tcpSocket->write(ps2_mode); // 写入数据块
        }
        delete serialPortThraed;
    }
}

/*ComboBox槽函数：获取当前comBox的文本*/
void rtspUI::getComboBoxText(QString text)
{
    if (!addingItem && text.compare("NONE")) {//防止添加item给comboBox触发该事件
        QVector<QString>::iterator iter = std::find(currentPlayDev.begin(), currentPlayDev.end(), text);
        if (iter == currentPlayDev.end()) {//防止重复播放一个地址
            qDebug() << "Not found this device in iter" << endl;
            currentPlayDev.insert(alreadyCreatVideo, text);//保存正在拉流的设备名称
            //if (alreadyCreatVideo < 4)
                //myVideoScrollArea->Big_devName.insert(alreadyCreatVideo, text);
            //currentPlayUrl.insert(alreadyCreatVideo, urlMap[text]);//保存拉流地址
            if (text.contains("4_3"))
                videoPlay(urlMap[text], text,alreadyCreatVideo, SCALE4_3);
            else
                videoPlay(urlMap[text], text, alreadyCreatVideo, SCALE16_9);
            alreadyCreatVideo++;//创建了videoLable 的标志位
        } else { //弹窗
            QMessageBox::information(this,
                                     tr("消息框"),
                                     tr("当前设备正在播放"),
                                     QMessageBox::Ok | QMessageBox::Cancel,
                                     QMessageBox::Ok);
        }
    }
}

/*----------------------------videoLabel slot function----------------------------*/
/*删除按钮槽函数*/
void rtspUI::deleteVideoLabelBtnClicked(int deleteDevNum)
{
    alreadyCreatVideo--;
    currentPlayDev.erase(currentPlayDev.begin() + deleteDevNum);
    //myVideoScrollArea->Big_devName.erase(myVideoScrollArea->Big_devName.begin() + devnum);
    //currentPlayUrl.erase(currentPlayUrl.begin() + devnum);
    my_videoLabel_list->remove(deleteDevNum);
    for (int i = 0; i < alreadyCreatVideo; i++) {
        videoLabel *my_video = my_videoLabel_list->get(i);
        if (i < 4)
            my_video->setGeometry(20 + (frame_width + INTERVAL) * (i % 2),
                                  100 + (frame_height + INTERVAL) * (i / 2), frame_width, frame_height);
        else
            my_video->move((frame_width + INTERVAL) * 2 + 20,
                           100 + (frame_height + INTERVAL) * (i - 4));
        my_video->setDevNum(i);
        my_video->subcomponentMove();
    }
    qDebug()<<"删除设备号："<<deleteDevNum<<"当前存在设备数："<<alreadyCreatVideo;
}

/*交换按钮槽函数*/
void rtspUI::changeVideoLabel(int devnum_1, int devnum_2)
{
    qDebug()<<"L_"<<devnum_1<<"与"<<"L_"<<devnum_2<<"开始交换";
    if (devnum_2 < alreadyCreatVideo) {
        my_videoLabel_list->change(devnum_1, devnum_2);

        videoLabel *my_video_1 = my_videoLabel_list->get(devnum_1);
        my_video_1->setGeometry(my_video_1->init_X, my_video_1->init_Y, my_video_1->width_, my_video_1->height_);
        my_video_1->subcomponentMove();

        videoLabel *my_video_2 = my_videoLabel_list->get(devnum_2);
        my_video_2->setGeometry(my_video_2->init_X, my_video_2->init_Y, my_video_2->width_, my_video_2->height_);
        my_video_2->subcomponentMove();

        qDebug()<<"L_"<<devnum_1<<"与"<<"L_"<<devnum_2<<"交换成功";
    } else {
        QMessageBox::about(NULL, "video", "没有这个videoLabel");
    }

}

/*----------------------------addurl win slot function----------------------------*/
/*与addurl连接的槽函数*/
void rtspUI::getMapData(QMap<QString, QString> map)
{
    for (QMap<QString, QString>::iterator iter = map.begin(); iter != map.end(); iter++) {
        if (urlMap.find(iter.key()) != map.end())
            urlMap[iter.key()] = map[iter.key()];//替换
        else
            urlMap.insert(iter.key(), map[iter.key()]);//加入
    }
    //qDebug()<<urlMap<<endl;
    addingItem = true;
    addComboBoxItem();/*给comboBox添加item*/
    addingItem = false;
}

/*----------------------------some ScrollArea slot functions 未实现，舍弃----------------------------*/
#if 0
/*与videoScrollArea交换videolabel, 默认当前videolabel至少存在5个*/
void rtspUI::changeVideoLabelFromScrollArea(int swap_scrollDevNum, int swap_uiDevNum)
{
    qDebug()<<"交换label部件";

    videoLabel *label_2 = my_videoLabel_list->get(swap_uiDevNum);
    videoLabel *label_1 = my_videoLabel_list->get(swap_scrollDevNum);
    label_1->setParent(this);
    label_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label_1->setGeometry(label_2->x(), label_2->y(), frame_width, frame_height);

    myVideoScrollArea->addVideoLabel(label_2, label_2->W_H_ratio);

    my_videoLabel_list->change(swap_scrollDevNum, swap_uiDevNum);
}

/*删除 ScrollArea 中的videolabel部件*/
void rtspUI::deleteVideoLabelFromScrollArea(int delate_scrollDevNum)
{
    my_videoLabel_list->remove(delate_scrollDevNum);
}
#endif

/*----------------------------serial----------------------------*/
/*选择串口窗口关闭*/
void rtspUI::serialPortWinClose(QObject *O)
{
    QString com = serialPortBox->currentText();
    serialPortThraed = new mySerialPort(this, com);
    connect(serialPortThraed, SIGNAL(getSerialPortData(uint8_t *, int)),
            this, SLOT(tcpSendData(uint8_t *, int)));
}


/*----------------------------T     C     P----------------------------*/
/*tcp 发送数据*/
void rtspUI::tcpSendData(uint8_t *ps2_data, int len)
{
    /* 如果已经连接 */
    char tcp_data[len * 4];
    int pos = 0; // 定义一个记录字符数组位置的变量
    for (int i = 0; i < len; i++) {
        pos += sprintf(tcp_data + pos, "%d ", ps2_data[i]); // 化为十进制的字符串
    }
    qDebug()<<"data:"<<tcp_data;
    if(tcpSocket->state() == tcpSocket->ConnectedState) {
        tcpSocket->write(tcp_data); // 写入数据块，需要指定长度
    }
}


/*tcp连接服务端*/
void rtspUI::tcpListen()
{
    qDebug()<<"tcp server listen...";
    tcpServer->listen(QHostAddress("192.168.137.1"), 8888);
}

/*tcp 连接成功*/
void rtspUI::tcpConnect()
{
    /* 获取客户端的套接字 */
    tcpSocket = tcpServer->nextPendingConnection();
    /* 客户端的ip信息 */
    QString str = "客户端IP地址:" + tcpSocket->peerAddress().toString();
    QMessageBox::about(NULL, "TCP 连接成功", str);

    connect(tcpSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(tcpSocketStateChange(QAbstractSocket::SocketState)));
}

/*tcp断开连接*/
void rtspUI::tcpStopConnect()
{
    qDebug()<<"stop listen"<<endl;

    tcpServer->close();

    /* 如果是连接上了也应该断开，如果不断开客户端还能继续发送信息，
     * 因为socket未断开，还在监听上一次端口 */
    if (tcpSocket->state() == tcpSocket->ConnectedState)
        tcpSocket->disconnectFromHost();
}

/*tcp连接状态改变*/
void rtspUI::tcpSocketStateChange(QAbstractSocket::SocketState state)
{
    switch (state) {
        case QAbstractSocket::UnconnectedState:
            QMessageBox::critical(NULL, "TCP", "网络断开连接，请关闭ps2手柄控制，网络恢复正常在开启");
            break;
        case QAbstractSocket::ConnectedState:
            qDebug()<<"socket 状态：ConnectedState"<<endl;
            break;
        case QAbstractSocket::ConnectingState:
            qDebug()<<"socket 状态：ConnectingState"<<endl;
            break;
        case QAbstractSocket::HostLookupState:
            qDebug()<<"socket 状态：HostLookupState"<<endl;
            break;
        case QAbstractSocket::ClosingState:
            qDebug()<<"socket 状态：ClosingState"<<endl;
            break;
        case QAbstractSocket::ListeningState:
            qDebug()<<"socket 状态：ListeningState"<<endl;
            break;
        case QAbstractSocket::BoundState:
            qDebug()<<"socket 状态：BoundState"<<endl;
            break;
        default:
            break;
    }
}