#include <QApplication>
#include "rtsp/rtspUI/rtspui.h"
#include "QPushButton"

rtspUI *pUi;
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    pUi = new rtspUI();
    return QApplication::exec();
}




