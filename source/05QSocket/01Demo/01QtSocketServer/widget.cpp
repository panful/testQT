#include "widget.h"

#include <iostream>
#include <thread>
#include <string>
#include <chrono>

#include <QTcpServer>
#include <QTcpSocket>

ServerWidget::ServerWidget(QWidget* parent)
    :QWidget(parent)
{
    std::cout << "=== Start ===\n";


    m_server = new QTcpServer(this);
    m_server->listen(QHostAddress::LocalHost, 8899); // 监听端口8899

    connect(m_server, SIGNAL(newConnection()), this, SLOT(OnNewConnection()));  // 当有客户端连接时，就会触发该信号
}

ServerWidget::~ServerWidget()
{
    std::cout << "===End===\n";
}

void ServerWidget::OnNewConnection()
{
    m_socket = m_server->nextPendingConnection();
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(OnRead())); // 当客户端有数据发送过来就会响应该信号

    //char buf[] = "abcd";
    int buf[] = { 1,2,3,4 };
    m_socket->write((char*)buf, sizeof(buf));
}

void ServerWidget::OnRead()
{
    char* buf = new char[1024];
    m_socket->read(buf, 1024);

    std::cout << buf << std::endl;
}



