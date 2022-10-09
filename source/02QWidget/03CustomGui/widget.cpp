

#ifdef TEST1

#include "widget.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    std::cout << "QWidget construct\n";
}

Widget::~Widget()
{
    std::cout << "QWidget destruct\n";
}

#endif // TEST1



