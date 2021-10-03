#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include "paperstack.h"
#include "tests.cpp"

class A {
public:
    int val;
    virtual int foo() const {
        return 1;
    }
};
class B : public A {
public:
    int other;
    virtual int foo() const override {
        return 2;
    }
};

template <typename Type>
int a(const A& p) {
    std::cout << p.foo() << std::endl << typeid(p).name();
    Type* type = new Type[4];
    std::cout << static_cast<PaperSheet>(type[0]).getWidth();
    return 1;
}

int main(int argc, char *argv[])
{
    testAllClasses();
    std::cout << "tests completed successfully";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
