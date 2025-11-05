//
// Created by 20648 on 2023/7/31.
//

#include "mysql.h"
#include <QDebug>
#include <qalgorithms.h>
#define mytable "dataTable"
#define CreateSQL
//#define dataup
//#define insertData
mysql::mysql(QObject *parent) : QObject(parent)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");//设置接入哪种数据库
    db.setDatabaseName("devURL.db");//给数据库命名
    if(!db.open())
        qDebug() << "数据库打开失败   " << db.lastError();//打印出创建失败的原因

    //就只运行一次
#ifdef CreateSQL
    if (!db.tables().contains("dataTable")) {
        qDebug() << "第一次创建dataTable数据库";
        createSql("dataTable(id int,devName varchar(20),devUrl varchar(50))");
    } else {
        qDebug() << "dataTable数据库已经创建";
    }

#endif

#ifdef insertData //插入数据
    insertSqlData(1, "RV1126", "rtsp://192.168.137.29:554/live/main_stream");
#endif
    getSqlData(mytable);

#ifdef dataup //数据修改
    amendSqlData(mytable, 1, "rtsp://192.168.137.29:554/live/main_stream");
    showSqlData(mytable);
#endif
}

mysql::~mysql()
{
    qDebug()<<"delete SQL";
}

/*创建*/
void mysql::createSql(QString table)
{
    QSqlQuery sql_query;
    QString create = "create table " + table;//dataTable(id int,devName varchar(20),devUrl varchar(50))
    sql_query.prepare(create);//创建数据库名称及其组成结构
    if(!sql_query.exec())
        qDebug() << "创建执行错误： " << sql_query.lastError();
    else
        qDebug() << "创建成功";
}

/*打印*/
void mysql::getSqlData(QString table)
{
    QSqlQuery sql_query;
    QString select_sql = "select * from " + table;//把table的全部内容显示出来
    sql_query.prepare(select_sql);
    if(!sql_query.exec()) {
        qDebug() << "查看执行错误： " << sql_query.lastError();
    }
    else {
        while(sql_query.next())//如果下一行数据还存在，就继续执行
        {
            int id = sql_query.value(0).toInt();//将sql里的int转换为qt里的int
            QString name = sql_query.value(1).toString();//将sql里的string转化为qt里的string
            QString url = sql_query.value(2).toString();
            sqlMap.insert(name, url);
            //qDebug() << "id: " << id << "devName: " << name << "  url: " << url ;
        }
    }
}

//槽函数
/*删除整个table*/
void mysql::deleteSqlDataAll(QString table)
{
    QSqlQuery sql_query;
    QString clear_sql = "delete from " + table;
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << "删除错误： " << sql_query.lastError();
    }
    else {
        qDebug() << "删除成功";
        sqlMap.clear();  // removes all items from the map
        getSqlData(mytable);
    }
}

/*删除table中的一个元素*/
void mysql::deleteSqlDataOne(QString table, QString name)
{
    QSqlQuery sql_query;
    QString delete_sql = "delete from " + table + " where devName=:n";
    sql_query.prepare(delete_sql);
    sql_query.bindValue(":n", name);
    if(!sql_query.exec())
    {
        qDebug() << "删除失败";
    }
    else {
        qDebug() << "删除成功";
        sqlMap.clear();  // removes all items from the map
        getSqlData(mytable);
    }
}

/*修改数据*/
void mysql::amendSqlData(QString table, QString name, QString url)
{
    QSqlQuery sql_query;
    QString update_sql = "update " + table + " set devUrl =:url where devName=:n";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":url",url);
    sql_query.bindValue(":n", name);

    if(!sql_query.exec()) {
        qDebug() << "更新失败" << sql_query.lastError();
    }
    else {
        qDebug() << "更新成功";
        getSqlData(mytable);
    }
}

/*插入数据*/
void mysql::insertSqlData(QString table, int id, QString name, QString url)
{
    QSqlQuery sql_query;
    //数据库对应数据输入
    QString insert_sql = "insert into " + table +" values(?,?,?)" ;
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(id);//id
    sql_query.addBindValue(name);//name
    sql_query.addBindValue(url);//url
    if(!sql_query.exec()) {
        qDebug() << "插入执行错误： " << sql_query.lastError();
    } else {
        qDebug() << "插入成功";
        getSqlData(mytable);
    }
}

/*传递数据*/
QMap<QString, QString> mysql::transferSqlData()
{
    return sqlMap;
}


