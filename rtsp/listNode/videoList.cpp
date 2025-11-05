//
// Created by 20648 on 2023/11/14.
//

#include "videoList.h"
#include <QDebug>
/*初始化链表为空*/
videoList::videoList(QObject *parent) : QObject(parent)
{
    list_head = nullptr;
    allDevNum = 0;
}

/*释放链表占用的内存*/
videoList::~videoList()
{
    myVideo_listNode *cur = list_head;
    while (cur != nullptr) {
        myVideo_listNode *tmp = cur->next;
        delete cur->my_video;
        delete cur;
        cur = tmp;
    }
}

/*在链表尾部插入一个节点*/
void videoList::append(int devNum, int width, int height, QWidget *parent)
{
    myVideo_listNode *newNode = new myVideo_listNode(devNum, width, height, parent); // 创建新节点
    if (list_head == nullptr) { // 如果链表为空，新节点就是头节点
        list_head = newNode;
    } else { // 如果链表不为空，找到尾节点，将其指针指向新节点
        myVideo_listNode *cur = list_head;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
    allDevNum++; // 设备加1
}

/*在链表头部插入一个节点*/
void videoList::prepend(int devNum, int width, int height, QWidget *parent)
{
    myVideo_listNode *newNode = new myVideo_listNode(devNum, width, height, parent); // 创建新节点
    newNode->next = list_head; // 将新节点的指针指向原头节点
    list_head = newNode; // 将新节点设为头节点
    allDevNum++; // 设备加1
}

/*在链表的第devNum个位置插入设备，如果无效，返回false，否则返回true*/
bool videoList::insert(int devNum, int width, int height, QWidget *parent)
{
    if (devNum < 0 || devNum > allDevNum) { // 检查index是否有效
        return false;
    }
    if (devNum == 0) { // 如果index为0，相当于在头部插入
        prepend(devNum, width, height, parent);
    } else if (devNum == allDevNum) { // 如果index为list_length，相当于在尾部插入
        append(devNum, width, height, parent);
    } else { // 如果index在中间，找到前一个节点，将其指针指向新节点，将新节点的指针指向后一个节点
        myVideo_listNode *newNode = new myVideo_listNode(devNum, width, height, parent); // 创建新节点
        myVideo_listNode *cur = list_head;
        for (int i = 0; i < devNum - 1; i++) { // 找到前一个节点
            cur = cur->next;
        }
        newNode->next = cur->next; // 将新节点的指针指向后一个节点
        cur->next = newNode; // 将前一个节点的指针指向新节点
        allDevNum++; // 设备加1

        cur = cur->next; //将当前节点指向新添加的节点
        while (cur->next != nullptr) { //将新节点后的所有节点中的devNum加1
            cur = cur->next;
            if (cur->next != nullptr) cur->my_video->thisDevnum += 1;
        }
    }
    return true;
}

/*删除链表的第devNum设备，如果无效，返回false，否则返回true*/
bool videoList::remove(int devNum)
{
    if (devNum < 0 || devNum >= allDevNum) { // 检查devNum是否有效
        return false;
    }
    if (devNum == 0) { // 如果devNum为0，相当于删除头节点
        myVideo_listNode *tmp = list_head; // 保存头节点
        list_head = list_head->next;// 将头节点设为下一个节点
        delete tmp->my_video;
        delete tmp; // 释放原头节点

        if (list_head != nullptr) {
            myVideo_listNode *cur = list_head;
            while (cur->next != nullptr) { //将删除节点后面的所有节点中的devNum减1
                cur->my_video->thisDevnum -= 1;
                cur = cur->next;
            }
        } else {
            qDebug()<<"链表为空";
        }
    } else { // 如果devNum不为0，找到前一个节点，将其指针指向后一个节点
        myVideo_listNode *cur = list_head;
        for (int i = 0; i < devNum - 1; i++) { // 找到前一个节点
            cur = cur->next;
        }
        myVideo_listNode *tmp = cur->next; // 保存要删除的节点
        cur->next = tmp->next; // 将前一个节点的指针指向后一个节点
        delete tmp->my_video;
        delete tmp; // 释放要删除的节点

        while (cur->next != nullptr) { //将删除节点后面的节点中的devNum减1 cur为前一个节点
            cur = cur->next;
            if(cur->next != nullptr) cur->my_video->thisDevnum -= 1;
        }
    }
    allDevNum--; // 设备减一
    return true;
}

/*交换位置*/
bool videoList::change(int devNum1, int devNum2)
{
    if (devNum1 < 0 || devNum1 >= allDevNum
                    || devNum2 < 0 || devNum2 >= allDevNum || devNum1 == devNum2) { // 检查devNum是否有效
        return false;
    }
    myVideo_listNode *list_1;
    myVideo_listNode *list_2;
    myVideo_listNode *list_1_pre = list_head;
    myVideo_listNode *list_2_pre = list_head;

    if (devNum1 == 0 || devNum2 == 0) {

        list_1 = list_head; // 其中一个必为头节点
        myVideo_listNode *list_2_pre = list_head;
        for (int i = 0; i < (devNum1 | devNum2) - 1; i++) {
            list_2_pre = list_2_pre->next; //list2前节点
        }
        list_2 = list_2_pre->next; //list2节点
        myVideo_listNode *list_2_next = list_2->next; //list2后节点

        if (abs(devNum1 - devNum2) > 1) { //两个部件之间有间隔
            list_head = list_2;
            list_2->next = list_1->next;
            list_2_pre->next = list_1;
            list_1->next = list_2_next;
        } else { //没有间隔
            list_head = list_2;
            list_2->next = list_1;
            list_1->next = list_2_next;
        }
    } else {
        /*获取list1前一个节点*/
        for (int i = 0; i < devNum1 - 1; i++)
            list_1_pre = list_1_pre->next;
        list_1 = list_1_pre->next; //list1节点
        /*获取list2前一个节点*/
        for (int i = 0; i < devNum2 - 1; i++)
            list_2_pre = list_2_pre->next;
        list_2 = list_2_pre->next; //list2节点
        myVideo_listNode *list_2_next = list_2->next; //list2后节点

        if (abs(devNum1 - devNum2) > 1) { //两个部件之间有间隔
            list_1_pre->next = list_2;
            list_2->next = list_1->next;

            list_2_pre->next = list_1;
            list_1->next = list_2_next;
        } else { //没间隔
            list_1_pre->next = list_2;
            list_2->next = list_1;
            list_1->next = list_2_next;
        }
    }

    /*交换*/
    swap_(list_2->my_video->thisDevnum, list_1->my_video->thisDevnum);
    swap_(list_2->my_video->init_X, list_1->my_video->init_X);
    swap_(list_2->my_video->init_Y, list_1->my_video->init_Y);
    swap_(list_2->my_video->width_, list_1->my_video->width_);
    swap_(list_2->my_video->height_, list_1->my_video->height_);

    return true;
}

// 获取链表的第index个节点的值，如果index无效，返回-1
videoLabel* videoList::get(int devNum) {
    if (devNum < 0 || devNum >= allDevNum) { // 检查index是否有效
        return NULL;
    }
    myVideo_listNode *cur = list_head;
    for (int i = 0; i < devNum; i++) { // 找到第index个节点
        cur = cur->next;
    }
    return cur->my_video; // 返回节点的值
}

void videoList::swap_(int &a,int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;
}