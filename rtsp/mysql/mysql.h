//
// Created by 20648 on 2023/7/31.
//

#ifndef QT_MYSQL_H
#define QT_MYSQL_H
#include <QObject>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQuery>
#include <QMap>

class mysql : public QObject{
Q_OBJECT
public:
    explicit  mysql(QObject *parent = nullptr);
    ~mysql() override;
public Q_SLOTS:
    void amendSqlData(QString table, QString name, QString url);//amend修改
    void insertSqlData(QString table, int id, QString name, QString url);
    void deleteSqlDataOne(QString table, QString name);
    void deleteSqlDataAll(QString table);

public:
    QMap<QString, QString> transferSqlData();
    QMap<QString, QString> sqlMap{};

private:
    void getSqlData(QString table);
    void createSql(QString table);
};


#endif //QT_MYSQL_H
