#include "ServerConnectForm.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ServerConnectForm window;
    window.show();
    return app.exec();
}

//test