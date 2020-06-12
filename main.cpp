#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "qmlRegister.h"
#include "imageprovider.h"
#include "imageproviderbridge.h"
#include <cpprest/http_client.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    //  register qml type
    registerQmlObject();

    //  qml engine
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    //  add image provider
    ImageProvider *pImageProvider = new ImageProvider;
    ImageProviderBridge *pImageProviderBridge = new ImageProviderBridge;
    pImageProviderBridge->setImageProvider(pImageProvider);
    engine.addImageProvider("imageProvider", pImageProvider);
    qmlRegisterSingletonInstance<ImageProviderBridge>("Sjyun.Desktop", 1, 0, "ImageProviderBridge", pImageProviderBridge);

    //  load first qml document
    const QUrl url(QStringLiteral("qrc:/qml/startup.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    //  application exec
    return app.exec();
}
