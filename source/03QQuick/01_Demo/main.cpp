#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    // warning C4996: 'Qt::AA_EnableHighDpiScaling': High-DPI scaling is always enabled. This attribute no longer has any effect.
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QGuiApplication app(argc, argv);

    //把item类型注册到qml中<Cpp类型>(qml模块名,主版本,次版本,qml类型)
    //qmlRegisterType<ViewerItem>("LearnOpenGL", 1, 0, "ViewerItem"); //模块名和qml中的import对应

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("QQuick.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
