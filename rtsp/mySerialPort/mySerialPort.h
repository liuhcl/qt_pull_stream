//
// Created by 20648 on 2023/12/11.
//

#ifndef QT_MYSERIALPORT_H
#define QT_MYSERIALPORT_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QVector>

class mySerialPort : public QObject
{
Q_OBJECT

public:
    explicit  mySerialPort(QObject *parent = nullptr, QString name = "");
    ~mySerialPort();

private:
    /*串口*/
    QSerialPort *serialPort;

    QString comName;
    uint8_t ps2_data[100];

Q_SIGNALS:
    void getSerialPortData(uint8_t *, int);

private Q_SLOTS:
    void getdata();

};


#endif //QT_MYSERIALPORT_H
