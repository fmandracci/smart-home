#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QScreen>
#include <QDebug>
#include <QDateTime>
#include <QDir>
#include <QQmlContext>
#include <QStandardPaths>

#include "application.h"


void logOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("[%1] Debug: %2").arg(QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss.zzz")).arg(msg);
        fprintf(stderr, "Debug: %s \n", msg.toLatin1().data());
        break;
    case QtWarningMsg:
        txt = QString("[%1] Warning: %2").arg(QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss.zzz")).arg(msg);
        fprintf(stderr, "Warning: %s \n", msg.toLatin1().data());
    break;
    case QtCriticalMsg:
        txt = QString("[%1] Critical: %2").arg(QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss.zzz")).arg(msg);
        fprintf(stderr, "Critical: %s \n", msg.toLatin1().data());
    break;
    case QtFatalMsg:
        txt = QString("[%1] Fatal: %2").arg(QDateTime::currentDateTime().toString("yyyy-MM-ddThh:mm:ss.zzz")).arg(msg);
        fprintf(stderr, "Fatal: %s \n", msg.toLatin1().data());
    break;
    }
    if(!QDir("LOGs").exists()) {
        QDir().mkdir("LOGs");
    }
    QString appName = QGuiApplication::applicationName();
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    qDebug()<<path;
    QFile outFile(path+"/LOGs/" + appName + "_" + QDate::currentDate().toString("yyyy-MM-dd")+".log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << Qt::endl;
}



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    //qInstallMessageHandler(logOutput);
    QQmlApplicationEngine engine;

    ///////// Expose Application to QML as Backend ///////////
    Application *appl = new Application();
    engine.rootContext()->setContextProperty("SmartEngine",appl);
    appl->start();
    //////////////////////////////////////////////////////////


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
