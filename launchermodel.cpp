#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QList>
#include <QNetworkInterface>

#include "launchermodel.h"
#include "spdlog/spdlog.h"

LauncherModel* LauncherModel::instance = nullptr;

LauncherModel* LauncherModel::getInstance() {
    if (instance == nullptr) {
        instance = new LauncherModel();
    }
    return instance;
}

QObject* LauncherModel::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine) {
    Q_UNUSED(scriptEngine)

    auto instance = LauncherModel::getInstance();
    engine->setObjectOwnership(instance, QQmlEngine::CppOwnership);
    return instance;
}

LauncherModel::LauncherModel(QObject *parent) : QObject(parent) {

}

QString LauncherModel::getAction() {
    spdlog::info("Get action, NOP");
    return "";
}

void LauncherModel::setAction(QString action) {
    spdlog::info("Définition d'une action : {}", action.toStdString());

    std::string filepath = "/tmp/robot-action";
    spdlog::debug("Ouverture du fichier en écriture", filepath);
    QFile file(filepath.c_str());
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream (&file);
        stream << action << '\n';
        file.close();
        spdlog::debug("Fermeture du fichier {}", filepath);
    }

    spdlog::info("Fermeture du lanceur");
    QGuiApplication::exit();
}

void LauncherModel::setNetworkInfo(QString value) {
    Q_UNUSED(value)

    this->networkInfo = "";
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;

    foreach(eth, allInterfaces) {
        QList<QNetworkAddressEntry> allEntries = eth.addressEntries();
        foreach (const QNetworkAddressEntry entry, allEntries) {
            if (entry.ip().protocol() != QAbstractSocket::IPv4Protocol || entry.ip().isLoopback()) {
                continue;
            }
            if (this->networkInfo.length() != 0) {
                this->networkInfo.append(", ");
            }

            this->networkInfo.append(entry.ip().toString())
                    .append(" (")
                    .append(eth.name())
                    .append(")");
        }
    }

    networkInfoChanged(this->networkInfo);

    // Check si on a un fichier externe
    QFile runFile("/tmp/external-dir/run");
    QFile monitoringFile("/tmp/external-dir/monitoring");
    QFile poweroffFile("/tmp/external-dir/poweroff");
    QFile rebootFile("/tmp/external-dir/reboot");
    if (runFile.exists()) {
        setAction("run");
    } else if (monitoringFile.exists()) {
        setAction("monitoring");
    } else if (poweroffFile.exists()) {
        setAction("poweroff");
    } else if (rebootFile.exists()) {
        setAction("reboot");
    }
}

QString LauncherModel::getNetworkInfo() {
    if (this->networkInfo == nullptr) {
        this->setNetworkInfo("");
    }
    return this->networkInfo;
}
