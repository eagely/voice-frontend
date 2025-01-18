#include <QApplication>
#include <src/core/mainwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumSize(400, 600);
    w.show();
    return a.exec();
}
