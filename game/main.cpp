#include "qipan.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qipan w;
    w.show();

    return a.exec();
}
