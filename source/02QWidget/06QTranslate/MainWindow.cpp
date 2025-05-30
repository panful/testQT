#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <QPushButton>

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout    = new QVBoxLayout(centralWidget);

    m_button        = new QPushButton(tr("Hello World!"), this);
    m_englishButton = new QPushButton(tr("English"), this);
    m_chineseButton = new QPushButton(tr("Chinese"), this);

    layout->addWidget(m_button);
    layout->addWidget(m_englishButton);
    layout->addWidget(m_chineseButton);

    setCentralWidget(centralWidget);
}
