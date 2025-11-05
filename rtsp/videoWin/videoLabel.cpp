//
// Created by 20648 on 2023/8/2.
//

#include "videoLabel.h"
#include "../rtspUI/rtspui.h"
#include <QMessageBox>
#include <QDebug>
#include <QHBoxLayout>

videoLabel::videoLabel(int width, int height, QWidget *parent) : QLabel(parent)
{
    width_ = width;
    height_ = height;
    this->resize(width, height);
    this->setScaledContents(true);//图片自适应大小
    //this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    magnifyBtnsClicked_times = 0;
    playBtnsClicked_times = 0;
    first_openRtspThread_flag = true;
    videoLabel_init();

    /*rtsp线程*/
    myRtsp = new rtsp;
    /*拉流线程*/
    myRtsp->moveToThread(&pullRtspThread);
    rtspThread_isPause = true; //刚开始创建的线程为暂停状态
    /*信号与槽*/
    slot_functions_init();
}

videoLabel::~videoLabel()
{
    qDebug()<<"正在关闭线程..."<<endl;
    /* 阻塞线程 2000ms，判断线程是否结束 */
    if (pullRtspThread.wait(2000))
        qDebug()<<"线程结束"<<endl;
    else
        qDebug()<<"线程关闭失败"<<endl;
}

void videoLabel::slot_functions_init()
{
    //播放按钮
    connect(this->playBtn, SIGNAL(clicked()), this, SLOT(playBtnsClicked()));
    //放大按钮
    connect(this->magnifyBtn, SIGNAL(clicked()), this, SLOT(magnifyBtnsClicked()));
    //刷新按钮
    connect(refreshBtn, SIGNAL(clicked()), this, SLOT(refreshBtnsClicked()));

    /* 接收到 myRtsp 发送过来的信号 */
    connect(myRtsp, &rtsp::sigData, this, &videoLabel::recv_frame_data);
    /* 发送开始工作的信号，开始工作 */
    connect(this, &videoLabel::start_pull_stream, myRtsp, &rtsp::pull_stream);
    /*rtsp error*/
    connect(myRtsp, &rtsp::readFrameErr, this, &videoLabel::read_frame_error);
    /*rtsp线程报错*/
    connect(myRtsp, &rtsp::sigErr, this, &videoLabel::rtspThread_err);

    /* 线程完成销毁对象 */
    connect(&pullRtspThread, SIGNAL(finished()), myRtsp, SLOT(deleteLater()));
    connect(&pullRtspThread, SIGNAL(finished()), &pullRtspThread, SLOT(deleteLater()));

}

/*获取rtsp拉流地址*/
void videoLabel::set_url_name(QString url, QString name)
{
    devurl = url;
    devname = name;
    devnameLabel = new QLabel(this);
    devnameLabel->setStyleSheet("background:transparent; color:#B55F32;");
    QFont font;
    font.setPointSize(8);
    font.setFamily("黑体");
    devnameLabel->setFont(font);
    devnameLabel->setFixedSize(80, 20);
    devnameLabel->move((this->width() - devnameLabel->width()) / 2, 0);
    devnameLabel->setText(devname);
}

/*获取设备号*/
void videoLabel::setDevNum(int devnum)
{
    thisDevnum = devnum;
    init_X = this->x();
    init_Y = this->y();
}

/*ui部件*/
void videoLabel::videoLabel_init(void)
{
    refreshBtn = new QPushButton(this);
    refreshBtn->setGeometry((this->width() - 150) / 2,
                            (this->height() - 150) / 2, 150, 150);
    refreshBtn->setStyleSheet("background:transparent");
    // refreshBtn->setEnabled(false);

    playBtn = new QPushButton(this);
    playBtn->setGeometry((this->width() - 150) / 2, (this->height() - 150) / 2,150, 150);
    playBtn->setStyleSheet("background:transparent");
    // playBtn->setWindowOpacity(0);//透明度  0完全透明
    // playBtn->setEnabled(true);

    // 创建一个按钮组
    buttonGroup = new QButtonGroup(this);
    // 将两个按钮添加到按钮组中
    buttonGroup->addButton(refreshBtn);
    buttonGroup->addButton(playBtn);
    // 设置按钮组的exclusive属性为false
    buttonGroup->setExclusive(false);
    // 设置初始显示的按钮为playBtn
    playBtn->setChecked(true);
    playBtn->setHidden(false);
    refreshBtn->setChecked(false);
    refreshBtn->setHidden(true);
    /*
    // 创建一个堆栈窗口部件
    btn_stackedWidget = new QStackedWidget(this);
    // 将两个按钮添加到堆栈窗口部件的不同层中
    btn_stackedWidget->addWidget(refreshBtn);
    btn_stackedWidget->addWidget(playBtn);
    // 设置初始显示的按钮为playBtn
    btn_stackedWidget->setCurrentWidget(playBtn);
    */

    magnifyBtn = new QPushButton(this);
    magnifyBtn->setFixedSize(32, 32);
    magnifyBtn->move(this->width() - 32, 0);
    magnifyBtn->setStyleSheet("background:transparent");
    magnifyBtn->setIcon(QIcon("D:/3-MyProject/pull_the_video_stream/images/[ ].png"));
    magnifyBtn->setIconSize(QSize(32, 32));

    imgLabel[0] = new QLabel(playBtn);
    imgLabel[0]->setStyleSheet("background:transparent");
    QPixmap playPix("D:/3-MyProject/pull_the_video_stream/images/play.png");
    imgLabel[0]->setPixmap(playPix);
    imgLabel[0]->setScaledContents(true);//图片自适应大小
    //imgLabel->raise();//放在顶层
    imgLabel[0]->resize(128, 128);
    imgLabel[0]->move((playBtn->width() - 128) / 2, (playBtn->height() - 128) / 2);

    imgLabel[1] = new QLabel(refreshBtn);
    imgLabel[1]->setStyleSheet("background:transparent");
    imgLabel[1]->setPixmap(QPixmap(""));
    imgLabel[1]->setScaledContents(true);//图片自适应大小
    //imgLabel->raise();//放在顶层
    imgLabel[1]->resize(128, 128);
    imgLabel[1]->move((refreshBtn->width() - 128) / 2, (refreshBtn->height() - 128) / 2);

    QSlider *bar = new QSlider(this);
    bar->setOrientation(Qt::Horizontal);  // 水平方向
    bar->setMinimum(0);  // 最小值
    bar->setMaximum(100);  // 最大值
    bar->setValue(99);  // 当前进度
    bar->setStyleSheet("QSlider{background:transparent;}"
                       "QSlider::groove:horizontal{border: 0px solid #bbb; background:transparent;}"
                       "QSlider::sub-page:horizontal"
                       "{background:#DEDCEB;border-radius: 5px;margin-top:12px;margin-bottom:12px;}"
                       "QSlider::add-page:horizontal"
                       "{background: #383C40;border: 1px solid #777;border-radius: 4px;margin-top:11px;margin-bottom:11px;}"
                       "QSlider::handle:horizontal"
                       "{background: #FFFFFF;width: 10px;border: 1px solid rgb(193,204,208);border-radius: 5px;margin-top:1px;margin-bottom:1px;}"
    );
    bar->move(80, this->height() - 30);
    bar->resize(600, 20);
    bar->setFixedHeight(20);
    bar->show();

    timeDurationLabel = new QLabel(this);
    timeDurationLabel->setStyleSheet("background:transparent; color:#ffffff;");
    QFont font;
    font.setPointSize(8);
    font.setFamily("黑体");
    timeDurationLabel->setFont(font);
    timeDurationLabel->setFixedSize(80, 20);
    timeDurationLabel->setText("00:00:00");

    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(timeDurationLabel);
    hBoxLayout->addWidget(bar);
    hBoxLayout->setAlignment(Qt::AlignBottom);

    // 设置子部件的大小策略为 Expanding
//    refreshBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    playBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    magnifyBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    timeDurationLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    bar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

/*rtsp线程与定时器开启*/
void videoLabel::openRtspThread()
{
    myRtsp->setUrl(devurl, thisDevnum);//拉流地址
    qDebug()<<devurl;
    /* 判断线程是否在运行 */
    if(!pullRtspThread.isRunning()) {
        /* 开启线程 */
        pullRtspThread.start();
        //qDebug()<<"开启RTSP线程";
    }
}

/*窗口显示大小*/
void videoLabel::widgetMove(bool screenIsFull)
{
    magnifyBtn->move(this->width() - 32, 0);
    if (screenIsFull) magnifyBtn->setIcon(QIcon("D:/3-MyProject/pull_the_video_stream/images/minimize.png"));
    else magnifyBtn->setIcon(QIcon("D:/3-MyProject/pull_the_video_stream/images/[ ].png"));

    playBtn->resize(this->width() - 60, this->height() - 60);
    playBtn->move(0, (this->height() - playBtn->height()) / 2);
    imgLabel[0]->move((playBtn->width() - 128) / 2, (playBtn->height() - 128) / 2);
}

/*窗口大小发生变化，移动子部件*/
void videoLabel::subcomponentMove()
{
    playBtn->resize(this->width() - 60, this->height() - 60);
    playBtn->move(0, (this->height() - playBtn->height()) / 2);
    imgLabel[0]->move((playBtn->width() - 128) / 2, (playBtn->height() - 128) / 2);
    magnifyBtn->move(this->width() - 32, 0);
    devnameLabel->move((this->width() - devnameLabel->width()) / 2, 0);

    width_ = this->width();
    height_ = this->height();
    init_X = this->x();
    init_Y = this->y();

    if (width_ == frame_width_320)
        magnifyBtn->setEnabled(false);
    else
        magnifyBtn->setEnabled(true);
}


/*----------------------------some slot functions----------------------------*/
//rtsp://192.168.137.29:554/live/main_stream 720*572
//rtsp://192.168.137.29:554/live/sub_stream 1920*1080
/*接收rtsp拉流数据*/
void videoLabel::recv_frame_data(uint8_t* data, int frameW, int frameH, bool pixel)
{
    //800, 600
    QImage image(data, frameW, frameH, pixel ? QImage::Format_ARGB32 : QImage::Format_Grayscale8);
    this->setPixmap(QPixmap::fromImage(image));
    //qDebug()<<"show video dev:"<<dev<<endl;
    av_free(data);
}

/*rtsp线程报错显示*/
void videoLabel::rtspThread_err(QString errStr)
{
    QString  str = "error" + QString::number(thisDevnum);
    char*  error;
    QByteArray ba = str.toLatin1(); // must
    error = ba.data();
    QMessageBox::critical(this, tr( error), errStr);

//
//    playBtnsClicked_times--;
//    first_openRtspThread_flag = true;
}

/*videoLabel部件的槽函数*/
void videoLabel::playBtnsClicked()
{
    qDebug()<<"当前设备号:"+ QString::number(thisDevnum)<<" afterInitThis:"<<first_openRtspThread_flag;
    if (first_openRtspThread_flag) {//只运行一次
        /*开启线程*/
        rtspThread_isPause = false;
        openRtspThread();
        emit start_pull_stream();
        /*等待设备连接成功*/

#if 0        //连接超时 这里没有做任何处理 要做处理的话 关闭线程就好 其实这里等待标志位就好
        int i = 0;
        while (!myRtsp->start_decodeStream_status) {
            i++;
            if (i > 1000 || myRtsp->rtsp_init_status == myRtsp->OPEN_FALSE) { /*设备连接失败*/
                myRtsp->rtsp_init_status = true;
                qDebug()<<"Failed device connection";
                return;
            }
            if (myRtsp->rtsp_init_status == myRtsp->OPEN_SUCCESS) break;
            QThread::msleep(100);
        }
        qDebug()<<"The device is connected successfully";
#endif
        /*设备连接成功*/
        myRtsp->start_decodeStream_status = false;
        first_openRtspThread_flag = false;
        imgLabel[0]->setPixmap(QPixmap("D:/3-MyProject/pull_the_video_stream/images/run.png"));
        timerID = startTimer(1000);//开启定时器
        playBtnsClicked_times++;
        return;
    }

    if (playBtnsClicked_times % 2 != 0) {
        rtspThread_isPause = true;
        QPixmap playPix("D:/3-MyProject/pull_the_video_stream/images/play.png");
        imgLabel[0]->setPixmap(playPix);
        myRtsp->pauseThread();//线程暂停
        removeImg_imgLabel = false;
        killTimer(timerID);//关闭定时器
    } else {
        rtspThread_isPause = false;
        QPixmap playPix("D:/3-MyProject/pull_the_video_stream/images/run.png");
        imgLabel[0]->setPixmap(playPix);
        timerID = startTimer(1000);//开启定时器
        if (playBtnsClicked_times != 0) myRtsp->resumeThread();//线程恢复
        removeImg_imgLabel = true;
    }
    playBtnsClicked_times++;
}

/*放大按钮槽函数*/
void videoLabel::magnifyBtnsClicked()
{
    if (magnifyBtnsClicked_times % 2 == 0) {
        init_X = this->x();
        init_Y = this->y();
        this->setGeometry(0, 0, 1920, 1080);
        this->raise();
        fullScreen = true;
    }
    else { //恢复部件原来位置
        this->setGeometry(init_X, init_Y, frame_width, frame_height);
        fullScreen = false;
    }
    this->widgetMove(fullScreen);
    magnifyBtnsClicked_times++;
}

/*定时器槽函数*/
void videoLabel::timerEvent(QTimerEvent *event)
{
    if (myRtsp->rtsp_init_status == myRtsp->OPEN_SUCCESS) secondAll++;
    if (removeImg_imgLabel) {
        imgLabel[0]->setPixmap(QPixmap(""));
        removeImg_imgLabel = false;
    }

    int second = secondAll % 60;
    int minute = secondAll / 60 % 60;
    int hour = secondAll / 3600;

    QString mediaDuration;
    mediaDuration.clear();

    if (hour >= 10)
        mediaDuration = QString::number(hour, 10);
    else
        mediaDuration = "0" + QString::number(hour, 10);

    if (minute >= 10)
        mediaDuration =  mediaDuration + ":" + QString::number(minute, 10);
    else
        mediaDuration =  mediaDuration + ":0" + QString::number(minute, 10);

    if (second >= 10)
        mediaDuration = mediaDuration + ":" + QString::number(second, 10);
    else
        mediaDuration = mediaDuration + ":0" + QString::number(second, 10);

    /*显示时间*/
    timeDurationLabel->setText(mediaDuration);
}

/*read frame error*/
void videoLabel::read_frame_error()
{
    killTimer(timerID);//关闭定时器
    //btn_stackedWidget->setCurrentWidget(refreshBtn);
    refreshBtn->setChecked(true);
    refreshBtn->setHidden(false);
    playBtn->setChecked(false);
    playBtn->setHidden(true);
    imgLabel[1]->setPixmap(QPixmap("D:/3-MyProject/pull_the_video_stream/images/refresh.png"));
}

/*刷新按钮*/
void videoLabel::refreshBtnsClicked()
{
    playBtn->setChecked(true);
    playBtn->setHidden(false);
    refreshBtn->setChecked(false);
    refreshBtn->setHidden(true);
    //btn_stackedWidget->setCurrentWidget(playBtn);
    imgLabel[1]->setPixmap(QPixmap("")); //清空

    myRtsp->restartThread();
    timerID = startTimer(1000);//开启定时器
}

/*鼠标进入事件*/
void videoLabel::enterEvent(QEvent *event)
{
    qDebug()<<"鼠标进入了:"<<devname;
    //mouseAtLabel = true;
}

/*鼠标离开事件*/
void videoLabel::leaveEvent(QEvent *event)
{
    qDebug()<<"鼠标离开了:"<<devname;
    if (deleteVideoLabelBtn != NULL) {
        delete deleteVideoLabelBtn;
        deleteVideoLabelBtn = NULL;

        delete changeVideoLabelBtn;
        changeVideoLabelBtn = NULL;
    }
    //mouseAtLabel = false;
}

/*鼠标点击事件*/
void videoLabel::mousePressEvent(QMouseEvent *event)
{
    const QPoint curPos = event->pos();
    int x = curPos.x();
    int y = curPos.y();
    // 如果是鼠标右键按下 第一次点击创建按钮 第二次点击删除按钮
    if(event->button() == Qt::RightButton && rtspThread_isPause) {
        if (mousePressTimes % 2 == 0) {
            deleteVideoLabelBtn = new pushBtn(80, 40, "删除", this);
            deleteVideoLabelBtn->move(x, y);
            deleteVideoLabelBtn->show();
            connect(deleteVideoLabelBtn, SIGNAL(clicked()), this, SLOT(deleteVideoLabelBtnClicked()));

            changeVideoLabelBtn = new pushBtn(80, 40, "交换", this);
            changeVideoLabelBtn->move(x, y + 40);
            changeVideoLabelBtn->show();
            connect(changeVideoLabelBtn, SIGNAL(clicked()), this, SLOT(changeVideoLabelBtnClicked()));
        } else {
            delete deleteVideoLabelBtn;
            deleteVideoLabelBtn = NULL;

            delete changeVideoLabelBtn;
            changeVideoLabelBtn = NULL;
        }
        mousePressTimes++;
    }
}

/*事件过滤器*/
/*
bool videoLabel::eventFilter(QObject *watched, QEvent *event)
{
    // 如果事件的类型是 QEvent::Enter，表示鼠标进入了部件的区域
    if (event->type() == QEvent::Enter) {
        mouseAtLabel = true;
        qDebug()<<"鼠标进入了:"<<devname;
        return false;
    } else if (event->type() == QEvent::Leave) {
        mouseAtLabel = false;
        qDebug()<<"鼠标离开了:"<<devname;
        return false;
    }
    // 其他事件交给父类处理
    return QWidget::eventFilter(watched, event);
}
*/
/*删除按钮槽函数*/
void videoLabel::deleteVideoLabelBtnClicked()
{
    qDebug()<<"删除设备名:"<<devname;
    /* 打断线程再退出 */
    myRtsp->stopThread();
    pullRtspThread.quit();
    emit deleteVideoLabel(thisDevnum);
}

/*交换按钮槽函数*/
void videoLabel::changeVideoLabelBtnClicked()
{
    changeLabelWin = new QWidget();
    changeLabelWin->resize(150, 50);
    changeLabelWin->setAttribute(Qt::WA_DeleteOnClose); //关闭按钮按下后，销毁该部件
    selectLabelBox = new QComboBox(changeLabelWin);
    selectLabelBox->setGeometry(12, 5, 150, 40);
    for (int i = 0; i < 6; i++) {
        if (i != thisDevnum) {
            selectLabelBox->addItem(QString::number(i));
        }
    }

    changeLabelWin->show();
    connect(changeLabelWin, SIGNAL(destroyed(QObject *)),
            this, SLOT(changeLabelWinClose(QObject *)));
}

/*交换窗口关闭*/
void videoLabel::changeLabelWinClose(QObject *)
{
    int changedDevNum = selectLabelBox->currentText().toInt();
    emit changeVideoLabel(thisDevnum, changedDevNum);
}