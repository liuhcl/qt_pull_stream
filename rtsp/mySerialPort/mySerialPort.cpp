//
// Created by 20648 on 2023/12/11.
//

#include "mySerialPort.h"
#include <QMessageBox>
#include <QDebug>

mySerialPort::mySerialPort(QObject *parent, QString name) : QObject(parent), comName(name)
{
    serialPort = new QSerialPort(this);
    /*设置波特率*/
    serialPort->setBaudRate(115200);
    /*设置串口名*/
    serialPort->setPortName(comName);
    /* 设置数据位数 */
    serialPort->setDataBits(QSerialPort::Data8);
    /* 设置奇偶校验 */
    serialPort->setParity(QSerialPort::NoParity);
    /* 设置停止位 */
    serialPort->setStopBits(QSerialPort::OneStop);
    /* 设置流控制 */
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    if (!serialPort->open(QIODevice::ReadWrite))
        QMessageBox::about(NULL, "错误", "串口无法打开！可能串口已经被占用！");

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(getdata()));
    QMessageBox::about(NULL, NULL, "串口已打开");
}

mySerialPort::~mySerialPort()
{
    QMessageBox::about(NULL, NULL, "关闭PS2远程控制");
}

/* 串口数据 */
void mySerialPort::getdata()
{
    // 读取串口数据
    QByteArray data = serialPort->readAll();
    int len = data.length();
    for (int i = 0; i < len; i++)
        ps2_data[i] = (uint8_t)data.at(i);

    QString str;
    for (int i = 0; i < len; i++) {
        str += QString::number(ps2_data[i]) + " ";
    }
    qDebug()<< "ps2 send data:" << str << "all data size:" << len;

    if (len == 5)
        emit getSerialPortData(ps2_data, len);
}



