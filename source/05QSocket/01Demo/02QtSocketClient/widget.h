#include <QWidget>

class QTcpServer;
class QTcpSocket;

class ClientWidget :public QWidget
{
    Q_OBJECT
public:
    explicit ClientWidget(QWidget* parent = nullptr);
    ~ClientWidget();

private slots:
    void OnSend();
    void OnWrite();
private:
    QTcpSocket* m_socket{ nullptr };
};