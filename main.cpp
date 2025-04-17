#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend/backendclient.h"
#include "backend/audioplayer.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    BackendClient backendClient("127.0.0.1", 8080);
    AudioPlayer audioPlayer;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("backend", &backendClient);
    engine.rootContext()->setContextProperty("audioPlayer", &audioPlayer);

    engine.clearComponentCache();
    qmlRegisterType<AudioPlayer>("dev.eagely.voice", 1, 0, "AudioPlayer");

#ifdef QT_DEBUG
    const QString qmlPath = QCoreApplication::applicationDirPath() + "/../../qml/Main.qml";
    qDebug() << "Loading QML from:" << qmlPath;
    engine.load(QUrl::fromLocalFile(qmlPath));
#else
    engine.load(QUrl("qrc:/qml/Main.qml"));
#endif

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
