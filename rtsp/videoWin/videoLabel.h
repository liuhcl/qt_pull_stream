//
// Created by 20648 on 2023/8/2.
//

#ifndef QT_VIDEOLABEL_H
#define QT_VIDEOLABEL_H

#include <QEvent>
#include <QLabel>
#include <QTimer>
#include <QMutex>
#include <QSlider>
#include <QThread>
#include <QPushButton>
#include <QButtonGroup>
#include <QComboBox>
#include "../rtsp.h"
#include "../rtspUI//pushBtn/pushBtn.h"

#define frame_width 720
#define frame_height 405
#define frame_width_320 320
#define frame_height_240 240

class videoLabel : public QLabel{
    Q_OBJECT
public:
    explicit videoLabel(int width, int height, QWidget *parent);
    ~videoLabel();

    void set_url_name(QString url, QString name);
    void setDevNum(int devnum);
    void openRtspThread();
    void widgetMove(bool);
    void subcomponentMove();

    int init_X;
    int init_Y;
    int width_;
    int height_;

    int W_H_ratio;
    bool fullScreen = false;
    bool winIsLarge = false;
    int thisDevnum;
    QPushButton *magnifyBtn;
    QPushButton *playBtn;
    QPushButton *refreshBtn;

private:
    rtsp *myRtsp;
    QLabel *imgLabel[2];
    QLabel *timeDurationLabel;
    pushBtn *deleteVideoLabelBtn = NULL;
    pushBtn *changeVideoLabelBtn  = NULL;
    QLabel *devnameLabel;
    QWidget *changeLabelWin;
    QComboBox *selectLabelBox;

    int mousePressTimes = 0;
    QString devurl;
    QString devname;
    bool rtspThread_isPause;
    bool removeImg_imgLabel = true;
    bool first_openRtspThread_flag = false;
    int playBtnsClicked_times;
    int magnifyBtnsClicked_times;
    int timerID;
    int secondAll = 0;
    QButtonGroup *buttonGroup;
    QThread pullRtspThread;

Q_SIGNALS:
    void start_pull_stream();
    void deleteVideoLabel(int);
    void changeVideoLabel(int, int);

private Q_SLOTS:
    void timerEvent(QTimerEvent *event) override;  //可以加override ，表示覆盖
    void recv_frame_data(uint8_t* data, int frameW, int frameH, bool pixel);
    void read_frame_error();
    void rtspThread_err(QString errStr);
    void playBtnsClicked();
    void magnifyBtnsClicked();
    void refreshBtnsClicked();
    void deleteVideoLabelBtnClicked();
    void changeVideoLabelBtnClicked();
    void changeLabelWinClose(QObject *);

private:
    //QStackedWidget *btn_stackedWidget;
    void slot_functions_init();
    void videoLabel_init(void);

protected:
    //void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *event) override; // 重写鼠标进入事件
    void leaveEvent(QEvent *event) override; // 重写鼠标离开事件
    //bool eventFilter(QObject *watched, QEvent *event) override; // 重写事件过滤器
};

#endif