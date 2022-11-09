#include "TriviadorGame.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TriviadorGame w;
    w.show();
    return a.exec();
}
