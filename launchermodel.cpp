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

QString LauncherModel::getIpAddress() {
    if (this->ipAddress == nullptr) {
        this->ipAddress = "";
        QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
        QNetworkInterface eth;

        foreach(eth, allInterfaces) {
            QList<QNetworkAddressEntry> allEntries = eth.addressEntries();
            foreach (const QNetworkAddressEntry entry, allEntries) {
                if (entry.ip().protocol() != QAbstractSocket::IPv4Protocol || entry.ip().isLoopback()) {
                    continue;
                }
                if (this->ipAddress.length() != 0) {
                    this->ipAddress.append(", ");
                }

                this->ipAddress.append(entry.ip().toString())
                        .append(" (")
                        .append(eth.name())
                        .append(")");
            }
        }

        ipAddressChanged();
    }

    return this->ipAddress;
}
