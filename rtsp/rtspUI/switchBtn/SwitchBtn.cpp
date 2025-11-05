//
// Created by 20648 on 2023/12/12.
//

#include "SwitchBtn.h"
#include <QPainter>

SwitchBtn::SwitchBtn(int w, int h, QWidget *parent) :
        QWidget(parent),
        m_bIsChecked(false)
{
    resize(w,h);
    m_pSwitchBtn = new QLabel(this);
    m_pSwitchBtn->setFixedSize(h, h);
    m_pSwitchBtn->setPixmap(QPixmap("D:/3-MyProject/pull_the_video_stream/images/switch_btn.png"));
    m_pSwitchBtn->setScaledContents(true);//图片自适应大小
    m_pSwitchBtn->move(QPointF(1,0).toPoint()); //向右偏移一个像素点

    m_pTBtnBg = new QPainterPath();
    m_pTBtnBg->moveTo(width(),height());
    m_pTBtnBg->setFillRule(Qt::WindingFill); //绘制复杂的图形路径
    m_pTBtnBg->addEllipse(w - h,0,h, h); //椭圆左上角x、y坐标以及宽度与边界矩形高度
    m_pTBtnBg->addEllipse(0,0,h, h);
    m_pTBtnBg->addRect(h * 0.5,0,w - h , h);

    m_pBtnAni = new QPropertyAnimation(m_pSwitchBtn,"pos",this);
    m_pBtnAni->setEasingCurve(QEasingCurve::Linear); //动画的进度和时间的比例是恒定的
    m_pBtnAni->setDuration(100);
}

SwitchBtn::~SwitchBtn()
{
    delete m_pBtnAni;
    delete m_pTBtnBg;
}

void SwitchBtn::setBtnChecked(bool check)
{
    m_bIsChecked = check;
    if(check)
    {
        m_pSwitchBtn->move(QPointF(width() - m_pSwitchBtn->height() - 1,0).toPoint());
    }
    else
    {
        m_pSwitchBtn->move(QPointF(1,0).toPoint());
    }
}

void SwitchBtn::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //设置抗锯齿渲染提示，以获得更好的视觉质量，平滑边缘
    painter.setPen(Qt::NoPen); //设置画笔为无边框
    if(m_bIsChecked)
    {
        painter.setBrush(QColor(34,169,173));
    }
    else
    {
        painter.setBrush(QColor(200,200,200));
    }
    painter.drawPath(*m_pTBtnBg); //使用选择的画刷和画笔设置绘制由 m_pTBtnBg 定义的路径
    QWidget::paintEvent(e);
}

void SwitchBtn::mouseReleaseEvent(QMouseEvent *e)
{
    _checkBtn();
    update(); //使用这个来触发paintEvent事件
    emit sigClicked(m_bIsChecked);
    QWidget::mouseReleaseEvent(e); //确保其他与鼠标释放事件相关的操作也能正常执行
}

void SwitchBtn::_checkBtn()
{
    if(m_pBtnAni)
    {
        if(m_pBtnAni->state() == QAbstractAnimation::Running)
        {
            return;
        }
        if(m_bIsChecked) //关闭
        {
            m_pBtnAni->setStartValue(QPointF(width()-height()-1,0).toPoint());
            m_pBtnAni->setEndValue(QPointF(1,0).toPoint());
        }
        else //打开
        {
            m_pBtnAni->setStartValue(QPointF(1,0).toPoint());
            m_pBtnAni->setEndValue(QPointF(width()-height()-1,
                                           0).toPoint());
        }
        m_pBtnAni->start();
        m_bIsChecked = !m_bIsChecked;
    }
}
