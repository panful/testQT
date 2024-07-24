#include <QApplication>
#include "widget.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    ServerWidget w;
    w.setWindowTitle("Server");
    w.setMinimumSize(800, 600);
    w.setMaximumSize(800, 600);
    w.show();

    return app.exec();
}
