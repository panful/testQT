#include <QWidget>

class QTcpServer;
class QTcpSocket;

class ServerWidget :public QWidget
{
    Q_OBJECT
public:
    explicit ServerWidget(QWidget* parent = nullptr);
    ~ServerWidget();

private slots:
    void OnRead();
    void OnNewConnection();
private:

    QTcpServer* m_server;
    QTcpSocket* m_socket;
};