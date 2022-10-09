
#include "window.h"
#include "ui_test.h"  //ui文件自动生成的头文件，也可以通过uic工具手动生成
#include <QPushButton>
#include <QHBoxLayout>
#include <QDialog>
#include <QWidget>

#include <iostream>

Window::Window(QWidget* parent) :
    QMainWindow(parent),
    ui(nullptr)
{
    QPushButton* btn = new QPushButton("TEST", this);
    btn->setGeometry(10, 10, 100, 60);
    connect(btn, SIGNAL(clicked()), this, SLOT(OnBtn1()));
}

Window::~Window()
{
    if (ui)
    {
        delete ui;
        ui = nullptr;
    }
}

void Window::OnBtn1()
{
    std::cout << "=================test\n";

    ui = new Ui::Dialog_UI();

    QDialog* dialog = new QDialog();
    this->ui->setupUi(dialog);
    dialog->exec();

}