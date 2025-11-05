//
// Created by 20648 on 2023/7/21.
//

#ifndef QT_RTSPUI_H
#define QT_RTSPUI_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QVector>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QComboBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>

#include "../rtsp.h"
#include "../videoWin/videoLabel.h"
#include "../addURL/addurl.h"
#include "../listNode/videoList.h"
#include "switchBtn/SwitchBtn.h"
#include "../mySerialPort/mySerialPort.h"
#include "videoScrollArea/videoScrollArea.h"

#define INTERVAL 50
QT_BEGIN_NAMESPACE
namespace Ui { class rtspUI; }
QT_END_NAMESPACE

class rtspUI : public QWidget {
Q_OBJECT

public:
    explicit rtspUI(QWidget *parent = nullptr);

    ~rtspUI() override;

private:
    Ui::rtspUI *ui;
    QMap<QString, QString> urlMap;
    QVector<QString> currentPlayDev;
    QVector<QString> currentPlayUrl;

    QWidget *serialPortWin;
    QComboBox *serialPortBox;
    mySerialPort *serialPortThraed;
    QPushButton *deleteVideoLabelBtn;
    SwitchBtn *mySwitchBtn;
    //videoScrollArea *myVideoScrollArea; /*未实现，舍弃*/
    /*ComboBox*/
    QStandardItemModel *pItemModel;
    QFont font;
    bool addingItem = false;

    addurl *AddUrl = nullptr;

    int alreadyCreatVideo = 0;
    int devnum;

    videoList *my_videoLabel_list;

    enum dev_num {
        ZERO,
        ONE,
        TWO,
        THREE,
        FORE
    };

private Q_SLOTS:
    void slotBtnClicked();
    void deleteVideoLabelBtnClicked(int);
    void changeVideoLabel(int, int);
    void getMapData(QMap<QString, QString> map);
    void getComboBoxText(QString);
    void switchBtnClicked(bool);
    void serialPortWinClose(QObject *);

    void tcpConnect();
    void tcpSocketStateChange(QAbstractSocket::SocketState);
    void tcpSendData(uint8_t *, int);

//    void changeVideoLabelFromScrollArea(int, int);
//    void deleteVideoLabelFromScrollArea(int);
//Q_SIGNALS:

private:
    void widgets_init();
    void setComboBox();
    void addComboBoxItem();
    void videoPlay(QString, QString, int, int);
    bool getFullScreenFlag();

    /* 通信套接字 */
    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;
    /*tcp 服务端聆听*/
    void tcpListen();
    /*tcp断开连接*/
    void tcpStopConnect();

protected:
    //重写虚函数
    //鼠标移动事件
//    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
};


#endif //QT_RTSPUI_H
