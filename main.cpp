#include "widget.h"
#include <QFileIconProvider>
#include <QFileInfo>
#include <QApplication>
#include  <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qssFile(":/lennetassist.qss");
    if(qssFile.open(QFile::ReadOnly))
    {
        QString qssStr = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qssStr);
    }
    Widget w;
    w.show();
    return a.exec();
}
