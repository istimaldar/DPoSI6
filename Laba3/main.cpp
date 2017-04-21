#include "mainwindow.h"
#include <QApplication>
#include "utils.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifndef DEBUG
    MainWindow w;
    w.show();
   return a.exec();
#elif
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            std::cout << Utils::rademacherFunction(j, (double)i / 16) << " ";
        }
        std::cout << std::endl;
    }
    return 0;
#endif
}
