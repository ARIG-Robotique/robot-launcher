#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QCursor>
#include <ctime>
#include <iostream>

#include "launchermodel.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace std;

void printUsage() {
    cerr << "Usage : robot-launcher [debug]" << endl;
}

void qDebugToSpdLog(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    Q_UNUSED(context)
    switch (type) {
        case QtDebugMsg:
            spdlog::debug(msg.toStdString());
            break;
        case QtInfoMsg:
            spdlog::info(msg.toStdString());
            break;
        case QtWarningMsg:
            spdlog::warn(msg.toStdString());
            break;
        case QtCriticalMsg:
        case QtFatalMsg:
            spdlog::error(msg.toStdString());
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 1) {
        printUsage();
        return 1;
    }

    const bool debug = argc >=3 && strcmp(argv[2], "debug") == 0;

    // Construit la date d'execution
    time_t now = time(nullptr);
    tm *ptm = localtime(&now);
    char timeBuffer[15];
    strftime(timeBuffer, 15, "%Y%m%d%H%M%S", ptm);

    const string outputDir = "logs/";
    const string outputPrefix = outputDir + string(timeBuffer);

    // configuration du logger
    //auto file_sink = make_shared<spdlog::sinks::basic_file_sink_mt>(outputPrefix + ".log");
    //spdlog::default_logger()->sinks().push_back(file_sink);
    //spdlog::flush_every(std::chrono::seconds(1));
    spdlog::set_level(debug ? spdlog::level::debug : spdlog::level::info);
    qInstallMessageHandler(qDebugToSpdLog);

    spdlog::info("Démarrage de l'application");

    // Enregistrement du model
    qmlRegisterSingletonType<LauncherModel>("org.arig.model", 1, 0, "LauncherModel", LauncherModel::singletonProvider);

    // QML Application
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

#ifdef RASPI
    app.setOverrideCursor(QCursor(Qt::BlankCursor));
#endif

    return app.exec();
}
