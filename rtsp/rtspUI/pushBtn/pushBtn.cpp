//
// Created by 20648 on 2023/12/22.
//

#include "pushBtn.h"

pushBtn::pushBtn(int w, int h, QString text, QWidget *parent) : QPushButton(parent)
{
    this->resize(w, h);
    this->setText(text);
    this->setStyleSheet(
            /*正常情况下样式*/
            "QPushButton{"
            "    color: #2f3640;"
            "    background-color: #f5f6fa;"
            "    border-color: #2f3640;"
            "    border-radius: 15px;"
            "    border-style: solid;"
            "    border-width: 2px;"
            "    padding: 5px;"
            "}"
            /*鼠标停留在按钮上的样式*/
            "QPushButton::hover{"
            "    color: #FFFFFF;"
            "    background-color: #E90925;"
            "    border-color: #2f3640;"
            "}"
            /*鼠标按压下去的样式*/
            "QPushButton::pressed,QPushButton::checked{"
            "    color: #FFFFFF;"
            "    background-color: #F38B00;"
            "}"
    );
}

pushBtn::~pushBtn()
{

}