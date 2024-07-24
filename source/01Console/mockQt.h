#include <QObject>

class MockQt :
    public QObject
{
    Q_OBJECT;

public:
    MockQt();
    ~MockQt() = default;

    //信号声明区
signals:
    void MySignal();
    void MySignal(int i);
    void MySignal(int m, int n);

    //槽函数声明区
private slots:
    void MySlot();
    void MySlot(int n);
    void MySlot(int m, int n);

public:
    void TestFunc(int i);
};