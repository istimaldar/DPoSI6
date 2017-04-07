#include "mainwindow.h"
#include <QApplication>
#include "utils.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*for (int i = 0; i < 1; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Utils::walshFunction(j, 0.5);
        }
    }*/
    MainWindow w;
    w.show();
    return a.exec();
}
