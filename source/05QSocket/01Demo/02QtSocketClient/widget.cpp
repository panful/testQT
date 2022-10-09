#include "widget.h"

#include <iostream>
#include <thread>
#include <string>
#include <chrono>

#include <QTcpServer>
#include <QTcpSocket>

ClientWidget::ClientWidget(QWidget* parent)
    :QWidget(parent)
{
    std::cout << "=== Start ===\n";

    m_socket = new QTcpSocket();
    m_socket->connectToHost(QHostAddress::LocalHost, 8899); // ip,port

    connect(m_socket, SIGNAL(connected()), this, SLOT(OnSend()));
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnWrite()));  // 当服务器有数据来，就会响应该信号  
    // readyRead【如果发送数据很大，会对这个数据包进行分包处理，而这个信号只能接收一个包的数据，所以就会出现接收不完全的情况】
}

void ClientWidget::OnSend()
{
    char buf[] = "1234";
    m_socket->write(buf, sizeof(buf)); //发送数据
}

ClientWidget::~ClientWidget()
{
    std::cout << "===End===\n";
}

void ClientWidget::OnWrite()
{
    char buf[1024] = { 0 };
    m_socket->read(buf, 1024);  // 读取数据
    std::cout << (int*)buf << std::endl;
    auto ret = (int*)buf;
    std::cout << ret[0] << ret[1] << ret[2];
}



