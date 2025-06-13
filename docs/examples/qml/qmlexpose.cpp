#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /* Load engine */
    QQmlApplicationEngine engine;
    //[...]

    /* Set context properties */
    tbq::QmlHelper qmlHelper;
    engine.rootContext()->setContextProperty("qmlHelper", &qmlHelper);

    /* Load QML modules */
    //[...]

    return app.exec();
}
