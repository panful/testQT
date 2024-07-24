
#include "window.h"
#include "ui_test.h"  //ui文件自动生成的头文件，也可以通过uic工具手动生成

#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>

#include <iostream>

Window::Window(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::TestUI)
{
    this->ui->setupUi(this);

    auto pBtn1 = new QPushButton("TEST");
    auto pLayout = new QHBoxLayout();
    auto pWidget = new QWidget();
    pLayout->addWidget(pBtn1);
    //pWidget->setLayout(pLayout);
    this->ui->widget1->setLayout(pLayout);

    connect(pBtn1, SIGNAL(clicked()), this, SLOT(OnBtn1()));
}

Window::~Window()
{
    delete ui;
}

void Window::OnBtn1()
{
    std::cout << "=================test\n";
}