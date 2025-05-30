/**
 * 1. setContextProperty	适合小型项目/快速原型，简单直接，无需注册，全局变量污染，难以维护
 * 2. qmlRegisterType QML_ELEMENT
 */

#define TEST1

#ifdef TEST1

#include "MyFunctions.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // 创建 MyFunctions 实例并注册为 QML 全局属性
    MyFunctions myFunctions;
    engine.rootContext()->setContextProperty("myFunctions", &myFunctions);

    const QUrl url(QStringLiteral("03_02_TEST1.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );
    engine.load(url);

    return app.exec();
}

#endif // TEST1

#ifdef TEST2

#include "MyFunctions.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    // 注册 MyFunctions 类型（命名空间可选）
    qmlRegisterType<MyFunctions>("MyFunctions", 1, 0, "MyFunctions");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("03_02_TEST2.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );
    engine.load(url);

    return app.exec();
}

#endif // TEST2
