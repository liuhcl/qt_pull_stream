//
// Created by 20648 on 2023/7/31.
//

#ifndef QT_ADDURL_H
#define QT_ADDURL_H

#include <QWidget>
#include <QString>
#include <QMap>
#include <QMessageBox>
#include <QTableWidget>
#include "../mysql/mysql.h"

#define mytable "dataTable"
QT_BEGIN_NAMESPACE
namespace Ui { class addurl; }
QT_END_NAMESPACE

class addurl : public QWidget {
Q_OBJECT

private:
    void popUpWin(bool add);
    void tableWidget_setItem();

public:
    explicit addurl(QWidget *parent = nullptr);

    ~addurl() override;

    QString getRtspUrl(QString name);
    QString getRtspName();

private:
    Ui::addurl *ui;
    QMap<QString, QString> urlMap{};
    /* QTabelWidgetItem 表格数据（项） */
    QTableWidgetItem *tableWidgetItem[16];

    mysql *sql;

    int staticDevNum;

Q_SIGNALS:
    void alreadyGetData(QMap<QString, QString> map);
    void insertData(QString table, int id, QString name, QString url);
    void amendData(QString table, QString name, QString url);
    void deleteDataOne(QString table, QString name);
    void deleteDataAll(QString table);
    //void deleteThis();

private Q_SLOTS:
    void addBtnClicked();
    void deleteBtnClicked();
};


#endif //QT_ADDURL_H
