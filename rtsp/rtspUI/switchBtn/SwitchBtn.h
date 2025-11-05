//
// Created by 20648 on 2023/12/12.
//

#ifndef QT_SWITCHBTN_H
#define QT_SWITCHBTN_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QLabel>

class SwitchBtn : public QWidget {
Q_OBJECT
public:
    explicit SwitchBtn(int w,int h,QWidget *parent = 0);
    ~SwitchBtn();
    void setBtnChecked(bool check);

protected:
    void paintEvent(QPaintEvent* e);
    void mouseReleaseEvent(QMouseEvent * e);
signals:
    void sigClicked(bool);
private:
    void _checkBtn();
private:
    QLabel * m_pSwitchBtn;
    bool m_bIsChecked;
    QPainterPath* m_pTBtnBg;
    QPropertyAnimation* m_pBtnAni;
};


#endif //QT_SWITCHBTN_H
