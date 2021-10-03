#include "mainwindow.h"
#include <QApplication>
#include "tests.cpp"

int main(int argc, char *argv[])
{
    testAllClasses();
    std::cout << "tests completed successfully";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
