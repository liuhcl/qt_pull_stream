//
// Created by 20648 on 2023/12/22.
//

#ifndef QT_PUSHBTN_H
#define QT_PUSHBTN_H

#include <QWidget>
#include <QPushButton>
#include <QString>

class pushBtn : public QPushButton{
Q_OBJECT
public:
    pushBtn(int w, int h, QString text, QWidget *parent);
    ~pushBtn();
};


#endif //QT_PUSHBTN_H
