#include "MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <QTranslator>

// ts 文件生成 qm 文件
// 命令行执行： lrelease.exe input.ts -qm output.qm

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 安装应用程序翻译
    QTranslator appTranslator {};
    if (appTranslator.load(":/MyTranslation/translation_zh_CN.qm"))
    {
        app.installTranslator(&appTranslator);
    }

    MainWindow window {};
    window.show();

    return app.exec();
}
