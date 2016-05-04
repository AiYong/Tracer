#include "LoginWidget.h"
#include <QApplication>
#include "MarketData.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<MarketData>("MarketData");
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();
    return a.exec();
}
