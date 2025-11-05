/********************************************************************************
** Form generated from reading UI file 'addurl.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDURL_H
#define UI_ADDURL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addurl
{
public:
    QLabel *tilte_label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *url_label;
    QLineEdit *urlEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *name_label;
    QLineEdit *nameEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *addButton;
    QTableWidget *tableWidget;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *delete_label;
    QLineEdit *deleteEdit;
    QPushButton *delete_btn;

    void setupUi(QWidget *addurl)
    {
        if (addurl->objectName().isEmpty())
            addurl->setObjectName(QString::fromUtf8("addurl"));
        addurl->resize(800, 600);
        tilte_label = new QLabel(addurl);
        tilte_label->setObjectName(QString::fromUtf8("tilte_label"));
        tilte_label->setGeometry(QRect(280, 20, 250, 35));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tilte_label->sizePolicy().hasHeightForWidth());
        tilte_label->setSizePolicy(sizePolicy);
        tilte_label->setMinimumSize(QSize(35, 20));
        tilte_label->setMaximumSize(QSize(10000, 10000));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(15);
        tilte_label->setFont(font);
        tilte_label->setAlignment(Qt::AlignCenter);
        layoutWidget = new QWidget(addurl);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 70, 661, 95));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        url_label = new QLabel(layoutWidget);
        url_label->setObjectName(QString::fromUtf8("url_label"));
        sizePolicy.setHeightForWidth(url_label->sizePolicy().hasHeightForWidth());
        url_label->setSizePolicy(sizePolicy);
        url_label->setMinimumSize(QSize(50, 20));
        url_label->setMaximumSize(QSize(10000, 10000));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(12);
        url_label->setFont(font1);

        horizontalLayout_2->addWidget(url_label);

        urlEdit = new QLineEdit(layoutWidget);
        urlEdit->setObjectName(QString::fromUtf8("urlEdit"));
        sizePolicy.setHeightForWidth(urlEdit->sizePolicy().hasHeightForWidth());
        urlEdit->setSizePolicy(sizePolicy);
        urlEdit->setMinimumSize(QSize(500, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        urlEdit->setFont(font2);
        urlEdit->setStyleSheet(QString::fromUtf8("border:2px groove gray;\n"
"border-radius:10px;\n"
"padding:2px 4px;"));

        horizontalLayout_2->addWidget(urlEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        name_label = new QLabel(layoutWidget);
        name_label->setObjectName(QString::fromUtf8("name_label"));
        sizePolicy.setHeightForWidth(name_label->sizePolicy().hasHeightForWidth());
        name_label->setSizePolicy(sizePolicy);
        name_label->setMinimumSize(QSize(50, 20));
        name_label->setMaximumSize(QSize(10000, 10000));
        name_label->setFont(font1);
        name_label->setLayoutDirection(Qt::LeftToRight);
        name_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(name_label);

        nameEdit = new QLineEdit(layoutWidget);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        sizePolicy.setHeightForWidth(nameEdit->sizePolicy().hasHeightForWidth());
        nameEdit->setSizePolicy(sizePolicy);
        nameEdit->setMinimumSize(QSize(500, 40));
        nameEdit->setFont(font2);
        nameEdit->setStyleSheet(QString::fromUtf8("border:2px groove gray;\n"
"border-radius:10px;\n"
"padding:2px 4px;"));

        horizontalLayout->addWidget(nameEdit);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        addButton = new QPushButton(layoutWidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setEnabled(true);
        sizePolicy.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
        addButton->setSizePolicy(sizePolicy);
        addButton->setMinimumSize(QSize(40, 40));
        addButton->setMaximumSize(QSize(10000, 1000));
        addButton->setStyleSheet(QString::fromUtf8("/**\346\255\243\345\270\270\346\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton{\n"
"    color: #FFFFFF;\n"
"    background-color: #45CC7F;\n"
"    border-color: #2f3640;\n"
"    border-radius: 15px;\n"
"    border-style: solid;\n"
"    border-width: 2px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\345\201\234\347\225\231\346\200\201*/\n"
"QPushButton:hover\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(44 , 137 , 255);\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\200\201*/\n"
"QPushButton:pressed\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(14 , 135 , 228);\n"
"    /*\345\267\246\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-left:5px;\n"
"    /*\344"
                        "\270\212\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-top:5px;\n"
"}\n"
""));

        horizontalLayout_3->addWidget(addButton);

        tableWidget = new QTableWidget(addurl);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(80, 170, 660, 350));
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        tableWidget->setMinimumSize(QSize(660, 350));
        tableWidget->setLineWidth(1);
        layoutWidget1 = new QWidget(addurl);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(260, 540, 306, 42));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        delete_label = new QLabel(layoutWidget1);
        delete_label->setObjectName(QString::fromUtf8("delete_label"));
        sizePolicy.setHeightForWidth(delete_label->sizePolicy().hasHeightForWidth());
        delete_label->setSizePolicy(sizePolicy);
        delete_label->setMinimumSize(QSize(50, 20));
        delete_label->setMaximumSize(QSize(10000, 10000));
        delete_label->setFont(font1);
        delete_label->setLayoutDirection(Qt::LeftToRight);
        delete_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(delete_label, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        deleteEdit = new QLineEdit(layoutWidget1);
        deleteEdit->setObjectName(QString::fromUtf8("deleteEdit"));
        sizePolicy.setHeightForWidth(deleteEdit->sizePolicy().hasHeightForWidth());
        deleteEdit->setSizePolicy(sizePolicy);
        deleteEdit->setMinimumSize(QSize(200, 40));
        deleteEdit->setFont(font2);
        deleteEdit->setStyleSheet(QString::fromUtf8("border:2px groove gray;\n"
"border-radius:10px;\n"
"padding:2px 4px;"));

        horizontalLayout_4->addWidget(deleteEdit);

        delete_btn = new QPushButton(layoutWidget1);
        delete_btn->setObjectName(QString::fromUtf8("delete_btn"));
        delete_btn->setEnabled(true);
        sizePolicy.setHeightForWidth(delete_btn->sizePolicy().hasHeightForWidth());
        delete_btn->setSizePolicy(sizePolicy);
        delete_btn->setMinimumSize(QSize(40, 40));
        delete_btn->setMaximumSize(QSize(40, 40));
        delete_btn->setStyleSheet(QString::fromUtf8("/**\346\255\243\345\270\270\346\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton{\n"
"    color: #FFFFFF;\n"
"    background-color: #45CC7F;\n"
"    border-color: #2f3640;\n"
"    border-radius: 15px;\n"
"    border-style: solid;\n"
"    border-width: 2px;\n"
"    padding: 5px;\n"
"	image: url(D:/3-MyProject/pull_the_video_stream/images/X.png);\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\345\201\234\347\225\231\346\200\201*/\n"
"QPushButton:hover\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(44 , 137 , 255);\n"
"}\n"
"\n"
"/*\346\214\211\351\222\256\346\214\211\344\270\213\346\200\201*/\n"
"QPushButton:pressed\n"
"{\n"
"    /*\350\203\214\346\231\257\351\242\234\350\211\262*/  \n"
"    background-color:rgb(14 , 135 , 228);\n"
"    /*\345\267\246\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\345\217\263\347\247\273\345\212\2503"
                        "\345\203\217\347\264\240*/  \n"
"    padding-left:5px;\n"
"    /*\344\270\212\345\206\205\350\276\271\350\267\235\344\270\2723\345\203\217\347\264\240\357\274\214\350\256\251\346\214\211\344\270\213\346\227\266\345\255\227\345\220\221\344\270\213\347\247\273\345\212\2503\345\203\217\347\264\240*/  \n"
"    padding-top:5px;\n"
"}\n"
""));

        horizontalLayout_4->addWidget(delete_btn);


        retranslateUi(addurl);

        QMetaObject::connectSlotsByName(addurl);
    } // setupUi

    void retranslateUi(QWidget *addurl)
    {
        addurl->setWindowTitle(QApplication::translate("addurl", "addurl", nullptr));
        tilte_label->setText(QApplication::translate("addurl", "<html><head/><body><p align=\"center\">\346\267\273\345\212\240\346\226\260\347\232\204\346\213\211\346\265\201\345\234\260\345\235\200</p></body></html>", nullptr));
        url_label->setText(QApplication::translate("addurl", "<html><head/><body><p align=\"center\">URL</p></body></html>", nullptr));
        name_label->setText(QApplication::translate("addurl", "<html><head/><body><p align=\"center\">name</p></body></html>", nullptr));
        addButton->setText(QString());
        delete_label->setText(QApplication::translate("addurl", "<html><head/><body><p align=\"center\">\345\210\240\351\231\244</p></body></html>", nullptr));
        delete_btn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class addurl: public Ui_addurl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDURL_H
