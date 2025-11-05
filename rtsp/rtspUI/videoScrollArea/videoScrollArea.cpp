//
// Created by 20648 on 2023/12/22.
//

#include "videoScrollArea.h"
#include <QPoint>
#include <QScrollBar>
#include <QRect>
#include <QDebug>
#include <QPushButton>

/*未实现，弃用*/
videoScrollArea::videoScrollArea(int w, int h, QWidget *parent) : QScrollArea(parent), label_width(w)
{
    resize(w, h);
    setFixedSize(w, h);
    myVBoxLayout = new QVBoxLayout();
    myVBoxLayout->setSpacing(50); //间隔

    // 设置滚动区域的属性
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏水平滚动条
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); //有需要时才显示
    this->setWidgetResizable (true); // 自动调整内部容器的宽度
    this->setAlignment (Qt::AlignHCenter); // 对齐
    this->setStyleSheet("background-color:transparent"); //设置背景透明
}

videoScrollArea::~videoScrollArea()
{

}

void videoScrollArea::addVideoLabel(videoLabel *myVideoLabel, int scale)
{
    qDebug()<<"scrollArea add label";
    myVideoLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    myVideoLabel->magnifyBtn->setEnabled(false);
    myVideoLabel->setParent(this); //更改父对象
    myVBoxLayout->addWidget(myVideoLabel); //添加部件
    if (scale == SCALE16_9)
        myVideoLabel->setMaximumSize(label_width, label_width/16*9);
    if (scale == SCALE4_3)
        myVideoLabel->setMaximumSize(label_width, label_width/4*3);

    this->setLayout(myVBoxLayout);
    //myVideoLabel->playBtn->move((this->width() - 150) / 2, (this->height() - 150) / 2);
    alldev++;
}

void videoScrollArea::removeVideoLabel()
{
    selectLabelWin = new QWidget();
    selectLabelWin->resize(150, 50);
    selectLabeBox->setAttribute(Qt::WA_DeleteOnClose); //关闭按钮按下后，销毁该部件
    selectLabeBox = new QComboBox(selectLabelWin);
    selectLabeBox->setGeometry(12, 5, 150, 40);

    for(int i = 0; i < 4; i++)
        selectLabeBox->addItem(Big_devName.at(i));

    selectLabelWin->show();
    connect(selectLabelWin, SIGNAL(destroyed(QObject *)),
            this, SLOT(selectLabelWinClose(QObject *)));
}

void videoScrollArea::deteleVideoLabel()
{
    QWidget *widget = this->widget(); // 获取内部容器的指针
    QList<QLabel*> videoLabels = widget->findChildren<QLabel*>(); // 获取内部容器的所有label
    if (!videoLabels.isEmpty()) // 如果列表不为空
    {
        QLabel *label = videoLabels.at(curPos_atDevNum); // 获取
        if (label) // 如果存在
        {
            qDebug()<<"scrollArea delete label";
            emit detaleVideoLabel(curPos_atDevNum + 4);
        }
    }
}

//鼠标移动函数参考
void videoScrollArea::mouseMoveEvent(QMouseEvent *e)
{
    QWidget::mouseMoveEvent(e); //调用父类函数
    QPoint pos = e->pos(); //鼠标位置
    QWidget *widget = this->widget(); // 获取内部容器的指针
    QScrollBar *vScroBall = this->verticalScrollBar(); //获取垂直滚动条指针
    int offset = 0;
    int dev = 0;
    if (widget) {
        if (vScroBall) offset = vScroBall->value();
        QList<QLabel*> videoLabels = widget->findChildren<QLabel*>(); // 获取内部容器的所有label
        for (auto label : videoLabels) {
            QRect rect = label->geometry(); //获取label的矩形区域
            rect.moveTop(rect.top() - offset); //根据偏移量调整label的区域
            dev++;
            if (rect.contains(pos)) { //鼠标位置是否处于区域内
                mousePos_atLabelAera = true;
                curPos_atDevNum = dev;
                qDebug()<<"当前设备号："<<curPos_atDevNum;
                break;
            }
        }
    }
}

//鼠标点击参考
void videoScrollArea::mousePressEvent(QMouseEvent *e)
{
    const QPoint curPos = e->pos();
    int x = curPos.x();
    int y = curPos.y();
    // 如果是鼠标右键按下 第一次点击创建按钮 第二次点击删除按钮
    if(e->button() == Qt::RightButton && mousePos_atLabelAera && alldev > 0) {
        if (mousePressTimes % 2 == 0) {
            if (btnWin != NULL) delete btnWin;
            btnWin = new QWidget(this);
            QVBoxLayout *vlayoutBtn = new QVBoxLayout(btnWin);
            pushBtn *deleteBtn = new pushBtn(80, 40, "移除", btnWin);
            pushBtn *removeBtn = new pushBtn(80, 40, "删除", btnWin);
            vlayoutBtn->setSpacing(0);
            vlayoutBtn->addWidget(removeBtn);
            vlayoutBtn->addWidget(deleteBtn);
            btnWin->move(x, y);
            btnWin->show();
            connect(removeBtn,SIGNAL(clicked()),this,SLOT(removeVideoLabel()));
            connect(deleteBtn,SIGNAL(clicked()),this,SLOT(deteleVideoLabel()));
        } else {
            delete btnWin;
        }
        mousePressTimes++;
    }
    mousePos_atLabelAera = false;
}

void videoScrollArea::selectLabelWinClose(QObject* O)
{
    int swapDevIndex = selectLabeBox->currentIndex();
    QWidget *widget = this->widget(); // 获取内部容器的指针
    QList<videoLabel*> videoLabels = widget->findChildren<videoLabel*>(); // 获取内部容器的所有label
    if (!videoLabels.isEmpty()) // 如果列表不为空
    {
        videoLabel *label = videoLabels.at(curPos_atDevNum); // 获取
        if (label) // 如果存在
        {
            qDebug()<<"scrollArea remove label";
            label->magnifyBtn->setEnabled(true);
            label->setParent(nullptr); //从父对象中移除
            myVBoxLayout->removeWidget(label); //从布局中移除label
            emit moveVideoLabel(4 + curPos_atDevNum, swapDevIndex);
        }
    }
}



