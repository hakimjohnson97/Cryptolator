#include <QApplication>
#include "Window.h"

int main(int argc, char* argv[])
{
    QApplication app (argc, argv);
    Window window;
    window.resize(600, 600);
    window.show();
    return app.exec();
}
