#include <QtGui/QApplication>
#include "toolkitwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToolkitWindow w;
    w.show();

    return a.exec();
}
