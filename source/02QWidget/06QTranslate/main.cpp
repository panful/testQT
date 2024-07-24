#include <QApplication>
#include <QTranslator>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;               //定义翻译器变量
    if (translator.load("MyTest.qm"))     //加载翻译文件
    {
        a.installTranslator(&translator); //安装翻译器
    }

    return a.exec();
}
