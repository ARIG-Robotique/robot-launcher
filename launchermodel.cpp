#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QList>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QTcpSocket>

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
    this->nerellStatus->start();
    this->overlordStatus->start();
    this->triangleStatus->start();
    this->carreStatus->start();
    this->rondStatus->start();
    this->starStatus->start();
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

void LauncherModel::refresh() {
    QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
    QNetworkInterface eth;

    this->networkInfo = "";
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
    emit networkInfoChanged(this->networkInfo);

    // Check hosts states
    this->nerellState = this->nerellStatus->getLastState();
    this->nerellAddress = this->nerellStatus->getAddress();
    emit nerellStateChanged(this->nerellState);
    emit nerellAddressChanged(this->nerellAddress);

    this->overlordState = this->overlordStatus->getLastState();
    this->overlordAddress = this->overlordStatus->getAddress();
    emit overlordStateChanged(this->overlordState);
    emit overlordAddressChanged(this->overlordAddress);

    this->triangleState = this->triangleStatus->getLastState();
    this->triangleAddress = this->triangleStatus->getAddress();
    emit triangleStateChanged(this->triangleState);
    emit triangleAddressChanged(this->triangleAddress);

    this->carreState = this->carreStatus->getLastState();
    this->carreAddress = this->carreStatus->getAddress();
    emit carreStateChanged(this->carreState);
    emit carreAddressChanged(this->carreAddress);

    this->rondState = this->rondStatus->getLastState();
    this->rondAddress = this->rondStatus->getAddress();
    emit rondStateChanged(this->rondState);
    emit rondAddressChanged(this->rondAddress);

    this->starState = this->starStatus->getLastState();
    this->starAddress = this->starStatus->getAddress();
    emit starStateChanged(this->starState);
    emit starAddressChanged(this->starAddress);

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
    return this->networkInfo;
}

int LauncherModel::getNerellState() {
    return this->nerellState;
}
QString LauncherModel::getNerellAddress() {
    return this->nerellAddress;
}

int LauncherModel::getOverlordState() {
    return this->overlordState;
}
QString LauncherModel::getOverlordAddress() {
    return this->overlordAddress;
}

int LauncherModel::getTriangleState() {
    return this->triangleState;
}
QString LauncherModel::getTriangleAddress() {
    return this->triangleAddress;
}

int LauncherModel::getCarreState() {
    return this->carreState;
}
QString LauncherModel::getCarreAddress() {
    return this->carreAddress;
}

int LauncherModel::getRondState() {
    return this->rondState;
}
QString LauncherModel::getRondAddress() {
    return this->rondAddress;
}

int LauncherModel::getStarState() {
    return this->starState;
}
QString LauncherModel::getStarAddress() {
    return this->starAddress;
}
