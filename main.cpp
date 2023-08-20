#include "tmwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    TMWindow w;
    w.show();
    QFile style(":/Style/Diffnes.qss");
    style.open(QIODevice::ReadOnly);
    auto currentStyle = style.readAll();
    a.setStyleSheet(currentStyle);
    a.setWindowIcon(QIcon(":/Icon/appicon.png"));
    style.close();
    return a.exec();
}
