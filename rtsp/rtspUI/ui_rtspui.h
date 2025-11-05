/********************************************************************************
** Form generated from reading UI file 'rtspui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTSPUI_H
#define UI_RTSPUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_rtspUI
{
public:
    QLabel *label_top;
    QWidget *hWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *rtspUI)
    {
        if (rtspUI->objectName().isEmpty())
            rtspUI->setObjectName(QString::fromUtf8("rtspUI"));
        rtspUI->resize(1000, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rtspUI->sizePolicy().hasHeightForWidth());
        rtspUI->setSizePolicy(sizePolicy);
        rtspUI->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        rtspUI->setFont(font);
        label_top = new QLabel(rtspUI);
        label_top->setObjectName(QString::fromUtf8("label_top"));
        label_top->setGeometry(QRect(0, 0, 160, 70));
        sizePolicy.setHeightForWidth(label_top->sizePolicy().hasHeightForWidth());
        label_top->setSizePolicy(sizePolicy);
        label_top->setMinimumSize(QSize(120, 50));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_top->setFont(font1);
        label_top->setLayoutDirection(Qt::LeftToRight);
        label_top->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: \"Microsoft YaHei\";\n"
"    font-size: 22px;\n"
"    color: #BDC8E2;\n"
"    font-style: normal;\n"
"    font-weight: normal;\n"
" \n"
"    border-style: solid;\n"
"    border-width: 2px;\n"
"    border-color: aqua;\n"
"    border-radius: 20px;\n"
" \n"
"    background-color: #2E3648;\n"
"    background-repeat: no-repeat;\n"
"    background-position: left center;\n"
"}\n"
"\n"
"\n"
"\n"
""));
        label_top->setAlignment(Qt::AlignCenter);
        hWidget = new QWidget(rtspUI);
        hWidget->setObjectName(QString::fromUtf8("hWidget"));
        hWidget->setGeometry(QRect(220, 0, 301, 70));
        sizePolicy.setHeightForWidth(hWidget->sizePolicy().hasHeightForWidth());
        hWidget->setSizePolicy(sizePolicy);
        hWidget->setMinimumSize(QSize(235, 70));
        horizontalLayout = new QHBoxLayout(hWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(hWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(151, 50));
        QFont font2;
        font2.setPointSize(12);
        comboBox->setFont(font2);
        comboBox->setStyleSheet(QString::fromUtf8("/*QCombobox\344\270\273\344\275\223*/\n"
"QComboBox {\n"
"    border: 2px solid #f3f3f3;/*\350\256\276\347\275\256\347\272\277\345\256\275*/\n"
"	background-color: rgb(237, 242, 255);/*\350\203\214\346\231\257\351\242\234\350\211\262*/\n"
"    border-radius: 15px;/*\345\234\206\350\247\222*/\n"
"    padding: 1px 2px 1px 2px;  /*\351\222\210\345\257\271\344\272\216\347\273\204\345\220\210\346\241\206\344\270\255\347\232\204\346\226\207\346\234\254\345\206\205\345\256\271*/\n"
"	text-align:bottom;\n"
"    min-width: 9em;   /*# \347\273\204\345\220\210\346\241\206\347\232\204\346\234\200\345\260\217\345\256\275\345\272\246*/\n"
"    /*min-height: 5em;*/\n"
"\n"
"	border-style:solid;/*\350\276\271\346\241\206\344\270\272\345\256\236\347\272\277\345\236\213*/\n"
"	border-width:2px;/*\350\276\271\346\241\206\345\256\275\345\272\246*/\n"
"	border-color:rgb(77, 123, 255);/*\350\276\271\346\241\206\351\242\234\350\211\262*/\n"
"\n"
"	padding-left: 10px;/*\345\267\246\344\276\247\350\276\271\350\267\235*/\n"
"}\n"
"/*QC"
                        "ombobox\345\217\263\344\276\247\346\214\211\351\222\256*/\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;/*\346\224\276\344\272\216\345\217\263\346\226\271\351\241\266\351\203\250*/\n"
"    width: 50px;/*\350\256\276\347\275\256\346\214\211\351\222\256\350\214\203\345\233\264\345\256\275\345\272\246*/\n"
" 	/*border-radius: 15px;\n"
"    border-left-width: 1px;\n"
"    border-left-color: darkgray;\n"
"    border-left-style: solid;*/\n"
"\n"
"    border-top-right-radius: 3px;/*\350\256\276\347\275\256\350\276\271\346\241\206\345\234\206\350\247\222*/\n"
"    border-bottom-right-radius: 3px;\n"
"/*padding-right: 50px;*/\n"
"}\n"
"/*QCombobox\345\217\263\344\276\247\346\214\211\351\222\256\347\232\204\347\256\255\345\244\264\345\233\276\346\240\207*/\n"
"QComboBox::down-arrow {\n"
"	border-image: url(D:/3-MyProject/pull_the_video_stream/images/downArrow.png);/*\350\207\252\345\256\232\344\271\211\345\233\276\347\211\207\345\241\253\345\205\205*/\n"
"	width: 2"
                        "0px;/*\350\256\276\347\275\256\350\257\245\345\233\276\346\240\207\347\232\204\345\256\275\351\253\230*/\n"
"	height: 20px;\n"
"}\n"
"\n"
"\n"
"/* \344\270\213\346\213\211\345\220\216\357\274\214\346\225\264\344\270\252\344\270\213\346\213\211\347\252\227\344\275\223\346\240\267\345\274\217 */\n"
"QComboBox QAbstractItemView {\n"
"    border: 2px solid #f3f3f3;/*\350\276\271\346\241\206\345\256\275\345\272\246\343\200\201\347\272\277\345\275\242\343\200\201\351\242\234\350\211\262*/\n"
"	background-color: rgba(237, 242, 255, 1);/*\350\203\214\346\231\257\351\242\234\350\211\262*/\n"
"    border-radius: 15px;/*\345\234\206\350\247\222*/\n"
"    padding: 1px 2px 1px 2px;  /*\351\222\210\345\257\271\344\272\216\347\273\204\345\220\210\346\241\206\344\270\255\347\232\204\346\226\207\346\234\254\345\206\205\345\256\271*/\n"
"    min-width: 9em;   /*# \347\273\204\345\220\210\346\241\206\347\232\204\346\234\200\345\260\217\345\256\275\345\272\246*/\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\345\220\216\357\274\214\346"
                        "\225\264\344\270\252\344\270\213\346\213\211\347\252\227\344\275\223\346\257\217\351\241\271\347\232\204\346\240\267\345\274\217 */\n"
"QComboBox QAbstractItemView::item {\n"
"	border-radius: 15px;/*\345\234\206\350\247\222*/\n"
"    height: 30px;   /* \351\241\271\347\232\204\351\253\230\345\272\246\357\274\210\350\256\276\347\275\256pComboBox->setView(new QListView());\345\220\216\357\274\214\350\257\245\351\241\271\346\211\215\350\265\267\344\275\234\347\224\250\357\274\211 */\n"
"	background-color: rgb(237, 242, 255);\n"
"\n"
"}\n"
"\n"
"/*\344\273\245\344\270\213\351\203\250\345\210\206\344\270\215\347\237\245\344\270\272\344\275\225\344\270\215\347\224\237\346\225\210\357\274\214\346\234\211\345\276\205\350\260\203\350\257\225*/\n"
"/* \344\270\213\346\213\211\345\220\216\357\274\214\346\225\264\344\270\252\344\270\213\346\213\211\347\252\227\344\275\223\350\266\212\350\277\207\346\257\217\351\241\271\347\232\204\346\240\267\345\274\217 */\n"
"QComboBox QAbstractItemView::item:hover {\n"
"    color: #FFF"
                        "FF0;\n"
"       /* \346\225\264\344\270\252\344\270\213\346\213\211\347\252\227\344\275\223\350\266\212\350\277\207\346\257\217\351\241\271\347\232\204\350\203\214\346\231\257\350\211\262 */\n"
"	background-color: rgb(98, 0, 255);\n"
"}\n"
"\n"
"/* \344\270\213\346\213\211\345\220\216\357\274\214\346\225\264\344\270\252\344\270\213\346\213\211\347\252\227\344\275\223\350\242\253\351\200\211\346\213\251\347\232\204\346\257\217\351\241\271\347\232\204\346\240\267\345\274\217 */\n"
"QComboBox QAbstractItemView::item:selected {\n"
"    color: #FFFFF0;\n"
"	background-color: rgb(0, 85, 200);\n"
"}\n"
"\n"
"\n"
"/* \347\202\271\345\207\273\344\270\213\346\213\211\347\256\255\345\244\264 */\n"
"QComboBox::down-arrow:on {\n"
"    image: url(D:/3-MyProject/pull_the_video_stream/images/downArrowClicked.png);   /* \346\230\276\347\244\272\344\270\213\346\213\211\347\256\255\345\244\264 */\n"
"	width: 20px;/*\350\256\276\347\275\256\350\257\245\345\233\276\346\240\207\347\232\204\345\256\275\351\253\230*/\n"
"	height: 20p"
                        "x;\n"
"}\n"
""));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(2, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(hWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(50, 50));
        pushButton->setStyleSheet(QString::fromUtf8("/**\346\255\243\345\270\270\346\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton{\n"
"    color: #2f3640;\n"
"    background-color: #f5f6fa;\n"
"    border-color: #2f3640;\n"
"    border-radius: 15px;\n"
"    border-style: solid;\n"
"    border-width: 2px;\n"
"    padding: 5px;\n"
"	image: url(D:/3-MyProject/pull_the_video_stream/images/+.png);\n"
"}\n"
"\n"
"/**\351\274\240\346\240\207\345\201\234\347\225\231\345\234\250\346\214\211\351\222\256\344\270\212\347\232\204\346\240\267\345\274\217**/\n"
"QPushButton::hover{	\n"
"    color: #FFFFFF;\n"
"    background-color: #718093;\n"
"    border-color: #2f3640;\n"
"}\n"
"\n"
"/**\351\274\240\346\240\207\346\214\211\345\216\213\344\270\213\345\216\273\347\232\204\346\240\267\345\274\217**/\n"
"QPushButton::pressed,QPushButton::checked{\n"
"    color: #FFFFFF;\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);\n"
"	image: url(D:/3-MyProject/pull_the_video_stream/images/+Clicked.pn"
                        "g);\n"
"}\n"
"\n"
"/**\346\214\211\351\222\256\345\244\261\350\203\275\346\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton::disabled{\n"
"    color: #FFFFFF;\n"
"    background-color: #dcdde1;\n"
"    border-color: #dcdde1;\n"
"}\n"
""));

        horizontalLayout->addWidget(pushButton);

        label = new QLabel(rtspUI);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(530, 10, 110, 50));
        label->setMinimumSize(QSize(110, 50));
        label->setMaximumSize(QSize(110, 50));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font3.setBold(true);
        font3.setItalic(false);
        font3.setUnderline(false);
        font3.setWeight(75);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    font-family: \"Microsoft YaHei\";\n"
"    font-size: 24px;\n"
"    color: #BDC8E2;\n"
"}"));

        retranslateUi(rtspUI);

        QMetaObject::connectSlotsByName(rtspUI);
    } // setupUi

    void retranslateUi(QWidget *rtspUI)
    {
        rtspUI->setWindowTitle(QApplication::translate("rtspUI", "rtspUI", nullptr));
        label_top->setText(QApplication::translate("rtspUI", "\346\213\211\346\265\201\350\247\206\351\242\221", nullptr));
        pushButton->setText(QString());
        label->setText(QApplication::translate("rtspUI", "PS2\346\211\213\346\237\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rtspUI: public Ui_rtspUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTSPUI_H
