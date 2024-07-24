#include <QGuiApplication>
#include <QQmlApplicationEngine>


// 报错：module "QtQuick" is not installed
// 添加环境变量QML2_IMPORT_PATH 值Qt/6.2.2/msvc2019_64/qml

int main(int argc, char* argv[])
{
    // warning C4996: 'Qt::AA_EnableHighDpiScaling': High-DPI scaling is always enabled. This attribute no longer has any effect.
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("03_01.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
