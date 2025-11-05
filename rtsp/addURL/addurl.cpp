//
// Created by 20648 on 2023/7/31.
//

// You may need to build the project (run Qt uic code generator) to get "ui_addurl.h" resolved

#include <mshtmlc.h>
#include <QDebug>
#include "addurl.h"
#include "ui_addurl.h"
#include "../rtspUI/rtspui.h"

addurl::addurl(QWidget *parent) : QWidget(parent), ui(new Ui::addurl)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);//关闭窗口执行析构函数
    setAttribute(Qt::WA_QuitOnClose, false); // 主窗口关闭后，该窗口也会关闭
    ui->tilte_label->setAlignment(Qt::AlignHCenter);//水平居中
    ui->horizontalLayout_3->setAlignment(Qt::AlignHCenter);//水平居中

    sql = new mysql(this);
    urlMap = sql->transferSqlData();//获取数据库数据

    ui->deleteEdit->setPlaceholderText("请输入设备名");

    ui->tableWidget->setColumnCount(2);/* 设置列数 */
    ui->tableWidget->setRowCount(2);/* 设置行数 */
    ui->tableWidget->verticalHeader()->setFixedWidth(30);//序列号宽
    ui->tableWidget->setColumnWidth(0, 130);//一列宽
    ui->tableWidget->setColumnWidth(1, 500);//第二列宽
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格不可被编辑

    /* 使用标签设置水平标题标签 */
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "设备" << "拉流地址");
    for (int i = 0; i < 16; i++) {
        /* 实例化 */
        tableWidgetItem[i] = new QTableWidgetItem("");
        /* 设置文本居中对齐 */
        tableWidgetItem[i]->setTextAlignment(Qt::AlignCenter);
    }
    tableWidget_setItem();//将数据库数据放入表格中
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addBtnClicked()));
    connect(ui->delete_btn, SIGNAL(clicked()), this, SLOT(deleteBtnClicked()));
    connect(this, &addurl::amendData, sql, &mysql::amendSqlData);
    connect(this, &addurl::insertData, sql, &mysql::insertSqlData);
    connect(this, &addurl::deleteDataOne, sql, &mysql::deleteSqlDataOne);
    connect(this, &addurl::deleteDataAll, sql, &mysql::deleteSqlDataAll);
    this->show();
}

addurl::~addurl() {
    qDebug()<<"delete addurl";
    staticDevNum = 0;
    //rtspUI::addComboBoxItem();
    delete ui;
}

/*获取对应设备的url*/
QString addurl::getRtspUrl(QString name)
{
    return urlMap[name];
}
/*获取对应设备的name*/
QString addurl::getRtspName()
{
    return ui->nameEdit->text();
}

/*表格*/
void addurl::tableWidget_setItem()
{
    int devNum = 0;
    /* 字符串类型链表 */
    QList<QString> strList;

    /*如果数据库为空*/
    if (urlMap.isEmpty()) return;

    for (QMap<QString, QString>::const_iterator it = urlMap.constBegin(); it != urlMap.constEnd(); it++) {
        strList << it.key() << it.value();
        devNum++;
    }

    for (int i = 0; i < devNum * 2; i++) {
        tableWidgetItem[i]->setText(strList[i]);
    }

    if (staticDevNum != devNum) {
        staticDevNum = devNum;
        ui->tableWidget->setRowCount(devNum);/* 设置行数 */
        /* 插入数据，表的 index 就是一个二维数组数据 */
        int row = 0, column = 0;
        for (int i = 0; i < devNum * 2; i++) {
            if (i > 0 && i % 2 == 0) row++;
            column = i % 2;
            ui->tableWidget->setItem(row, column, tableWidgetItem[i]);
        }
    }

}

/*弹窗*/
void addurl::popUpWin(bool add)
{
    urlMap = sql->transferSqlData();//获取数据库数据
    tableWidget_setItem();
    emit alreadyGetData(urlMap);//发送接收到数据的信号
    QMessageBox::information(this,
                             tr("消息框"),
                             add ? tr("添加成功") : tr("删除成功"),
                             QMessageBox::Ok | QMessageBox::Cancel,
                             QMessageBox::Ok);
}

/*按钮槽函数：添加新的url*/
void addurl::addBtnClicked()
{
    QString name;
    int devNum;
    bool alreadyHaveThisDev = false;
    name = ui->nameEdit->text();
    if (name.isEmpty()) return;
    for(QMap<QString, QString>::iterator iter = urlMap.begin(); iter != urlMap.end(); iter++, devNum++) {
        if (iter.key() == name) {
            qDebug()<<"有这个key"<<endl;
            alreadyHaveThisDev = true;
            break;
        }
    }

    qDebug()<< "插入的设备ID:" << devNum;
    if (alreadyHaveThisDev) {//存在则覆盖
        emit amendData(mytable, ui->nameEdit->text(), ui->urlEdit->text());
    } else {//不存在则插入
        emit insertData(mytable, devNum + 1, name, ui->urlEdit->text());//获取拉流地址及名称
    }
    popUpWin(true);//弹窗
}

void addurl::deleteBtnClicked() {
    if (ui->deleteEdit->text() == "all") {
        emit deleteDataAll(mytable);//删除表中所有数据
        popUpWin(false);//弹窗
    } else {
        for (QMap<QString, QString>::iterator iter = urlMap.begin(); iter != urlMap.end(); iter++) {
            if (iter.key() == ui->deleteEdit->text()) {
                emit deleteDataOne(mytable, ui->deleteEdit->text());
                popUpWin(false);//弹窗
                return;
            }
        }
        QMessageBox::critical(this,tr("ERROR"),tr("没有这个设备"));
    }
}