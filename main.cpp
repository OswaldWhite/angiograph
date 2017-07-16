#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "screenshot.h"

    void main(int argc, char *argv[])
    {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QGuiApplication app(argc, argv);

        qmlRegisterType<ScreenShot>("screenshot", 1, 0, "Screenshot");

        QQmlApplicationEngine engine;
        engine.load(QUrl(QLatin1String("qrc:/main.qml")));

        app.exec();
    }
