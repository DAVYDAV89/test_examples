
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QDebug>
#include <unistd.h>

#include "threadbuffer.h"

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    ThreadBuffer appCore;
    QQmlContext *context = engine.rootContext();

    context->setContextProperty("appCore", &appCore);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    for (int i = 0; i < 10; ++i ){
//        sleep(1);
//        qDebug() << "i: " << i;
//    }

    return app.exec();
}
