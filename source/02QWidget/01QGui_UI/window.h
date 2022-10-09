
#include <QMainWindow>
#include <QPushButton>

// 注意生成的ui_***.h文件中命名空间的名字
namespace Ui
{
    class TestUI; //TestUI就是ui文件中QMianWindow的QObjectName
}

class Window :public QMainWindow
{
    Q_OBJECT;
public:
    explicit Window(QWidget* parent = nullptr);
    ~Window();

private slots:
    void OnBtn1();

private:
    Ui::TestUI* ui;
};