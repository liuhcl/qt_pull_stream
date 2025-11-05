//
// Created by 20648 on 2023/12/22.
//

#ifndef QT_VIDEOSCROLLAREA_H
#define QT_VIDEOSCROLLAREA_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QVector>
#include <QMouseEvent>
#include "../../videoWin/videoLabel.h"
#include "../pushBtn/pushBtn.h"

/*未实现，弃用*/
#define SCALE16_9 169
#define SCALE4_3 43

class videoScrollArea : public QScrollArea{
Q_OBJECT

public:
    videoScrollArea(int w,int h, QWidget *parent = nullptr);
    ~videoScrollArea();

    int curPos_atDevNum;
    QVector<QString> Big_devName;
    void addVideoLabel(videoLabel *myVideoLabel, int scale);

private:
    QVBoxLayout *myVBoxLayout;

    QWidget *selectLabelWin;
    QComboBox *selectLabeBox;

    bool mousePos_atLabelAera = false;
    int label_width;
    int mousePressTimes = 0;
    int alldev = 0;
    QWidget *btnWin;

Q_SIGNALS:
    void moveVideoLabel(int, int);
    void detaleVideoLabel(int);

private Q_SLOTS:
    void removeVideoLabel();
    void deteleVideoLabel();
    void selectLabelWinClose(QObject*);

protected:
    void mouseMoveEvent(QMouseEvent *e); // 重写鼠标移动事件
    void mousePressEvent(QMouseEvent *e);

};


#endif //QT_VIDEOSCROLLAREA_H
