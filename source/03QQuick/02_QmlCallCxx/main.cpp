
/*
1. setContextProperty qml调用C++函数
2. qmlRegisterSingletonType qml调用C++函数
3. qml
*/

#define TEST1

#ifdef TEST1

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "QDataMgr.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QDataMgr data_mgr;
    engine.rootContext()->setContextProperty("DATAMGR", &data_mgr);
    engine.load(QUrl(QStringLiteral("03_02.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}

#endif // TEST1

#ifdef TEST2

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qdatamgr.h"

static QObject* qDataMgrSingletonFactory(QQmlEngine*, QJSEngine*)
{
    QDataMgr* dmgrGlobal = new QDataMgr();

    return dmgrGlobal;
}


int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //qmlRegisterSingletonType<QDataMgr>("MyTestV", 2, 0, "DATAMGR", qDataMgrSingletonFactory);
    qmlRegisterSingletonType<QDataMgr>("MyTestV", 2, 0, "DATAMGR", [](QQmlEngine*, QJSEngine*)->QObject* {return new QDataMgr(); });
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}

#endif // TEST2

#ifdef TEST3

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("main.qml")));

    return app.exec();
}

#endif // TEST3

