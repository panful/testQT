#include "mockQt.h"
#include <iostream>

MockQt::MockQt() {
    // 信号与槽函数连接
    this->connect(this, SIGNAL(MySignal()), SLOT(MySlot()));
    connect(this, SIGNAL(MySignal(int)), this, SLOT(MySlot(int))); //receive如果是this可写可不写
    connect(this, SIGNAL(MySignal(int, int)), SLOT(MySlot(int, int)));
}

void MockQt::MySlot() {
    std::cout << "mySlot()\n";
}
void MockQt::MySlot(int n) {
    std::cout << "mySlot(int n)\tn = " << n << '\n';
}
void MockQt::MySlot(int m, int n) {
    std::cout << "mySlot(int m,int n)\tm = " << m << "\tn = " << n << '\n';
}

void MockQt::TestFunc(int i) {
    switch (i)
    {
    case 0:
        emit MySignal(); // 发射信号
        break;
    case 1:
        emit MySignal(99);
        break;
    case 2:
        emit MySignal(88, 77);
        break;
    default:
        break;
    }
}