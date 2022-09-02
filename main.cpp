
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <unistd.h>

#include "threadbuffer.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Создаем экземпляр класса.
    ThreadBuffer _threadBuffer;

//    for (int i = 0; i < 10; ++i ){
//        sleep(1);
//        qDebug() << "i: " << i;
//    }

    return app.exec();
}
