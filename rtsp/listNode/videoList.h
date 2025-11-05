//
// Created by 20648 on 2023/11/14.
//

#ifndef QT_VIDEOLIST_H
#define QT_VIDEOLIST_H
#include <QObject>
#include "../videoWin/videoLabel.h"

class videoList : public QObject{

public:
    struct myVideo_listNode {
        videoLabel *my_video;
        struct myVideo_listNode *next;
        // 构造函数，初始化节点值和指针
        myVideo_listNode(int devNum, int width, int height, QWidget *parent) : next(nullptr) {
            my_video = new videoLabel(width, height, parent);
            my_video->thisDevnum = devNum;
        }
    };

public:
    explicit  videoList(QObject *parent = nullptr);
    ~videoList() override;

    myVideo_listNode *list_head;
    int allDevNum;

    void append(int devNum, int width, int height, QWidget *parent);
    void prepend(int devNum, int width, int height, QWidget *parent);
    bool insert(int devNum,  int width, int height, QWidget *parent);
    bool remove(int devNum);
    bool change(int devNum1, int devNum2);
    videoLabel* get(int devNum);

private:
    void swap_(int &a,int &b);
};


#endif //QT_VIDEOLIST_H
