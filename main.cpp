#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>
#include <QQmlProperty>
#include <QQuickView>

//【2】Transform QQuickItem and Set / Get Property
#include <QQuickItem>
//【5】Signals and Slots
#include "cpp_code.h"

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

    //【0】Load .qml file (2 Methods)
    // Register Method 1 (root can't be Window)
    QQuickView view(QUrl("qrc:/qmlWindow.qml"));
    view.show();
    QObject *qmlWindow = view.rootObject();

    // Register Method 2
    QQmlComponent compont(&engine);
    compont.loadUrl(QUrl(QString("qrc:/qmlWindow2.qml")));
    QObject *qmlWindow_2 = compont.create();
    qmlWindow_2->setParent(engine.rootObjects()[0]);
    // Expose QObject *qmlWindow_2 to main.qml, name is "qmlWindows_2".
    engine.rootContext()->setContextProperty("qmlWindows2", qmlWindow_2);

    //【1】Set ( 2 methods ) and Get Property
    qmlWindow->setProperty("height", 400); // Set Method 1
    QQmlProperty(qmlWindow, "height").write(400); // Set Method 2
    qDebug() << "Cpp get qml property height" << qmlWindow->property("height");
    qDebug() << "Cpp get qml property msg" << qmlWindow->property("msg_name");

    //【2】Transform to QQuickItem type and Set and Get Property
    QQuickItem *item = qobject_cast<QQuickItem*>(qmlWindow);
    item->setWidth(400);
    qDebug() << "Cpp get qml property width" << item->width();

    //【3】Use QObject::findChildren() to find children under the root
    QObject *qmlRect = qmlWindow->findChild<QObject*>("rectangle");
    if(qmlRect){
        qmlRect->setProperty("color", "white");
        qDebug() << "Cpp get rect color" << qmlRect->property("color");
    }

    //【4】Use the function in .qml file
    QVariant val_return; // must be QVariant type
    QVariant val_arg = "Kris.Suuuu";  // must be QVariant type
    QVariant val_arg2 = 1997;  // must be QVariant type
    QMetaObject::invokeMethod(qmlWindow,
                              "qml_method",
                              Q_RETURN_ARG(QVariant, val_return),
                              Q_ARG(QVariant, val_arg),
                              Q_ARG(QVariant, val_arg2));
    qDebug() << "QMetaObject::invokeMethod result" << val_return;

    //【5】Signals and Slots
    cpp_code cppObj;
    // QML -> CPP, Use QString / int ... type
    QObject::connect(qmlWindow, SIGNAL(qmlSendMsg(QString,int)),
                     &cppObj, SLOT(cppRecvMsg(QString,int)));
    // CPP -> QML, Use QVariant type
    QObject::connect(&cppObj, SIGNAL(cppSendMsg(QVariant,QVariant)),
                     qmlWindow, SLOT(qmlRecvMsg(QVariant,QVariant)));

    return app.exec();
}
