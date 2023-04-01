#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "mymodeltable.h"
#include "threadbuffer.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ThreadBuffer appCore;
    QQmlContext *context = engine.rootContext();
    MyModelTable *model = new MyModelTable;

    context->setContextProperty("appCore", &appCore);

    engine.rootContext()->setContextProperty("myModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
