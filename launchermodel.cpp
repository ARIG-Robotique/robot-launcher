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
    this->updateRobotStates("nerell", &this->nerellState, &this->nerellAddress);
    emit nerellStateChanged(this->nerellState);
    emit nerellAddressChanged(this->nerellAddress);

    this->updateRobotStates("overlord", &this->overlordState, &this->overlordAddress);
    emit overlordStateChanged(this->overlordState);
    emit overlordAddressChanged(this->overlordAddress);

    this->updateRobotStates("pami-triangle", &this->triangleState, &this->triangleAddress);
    emit triangleStateChanged(this->triangleState);
    emit triangleAddressChanged(this->triangleAddress);

    //this->updateRobotStates("pami-carre", &this->carreState, &this->carreAddress);
    //emit carreStateChanged(this->carreState);
    //emit carreAddressChanged(this->carreAddress);

    //this->updateRobotStates("pami-rond", &this->rondState, &this->rondAddress);
    //emit rondStateChanged(this->rondState);
    //emit rondAddressChanged(this->rondAddress);

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

void LauncherModel::updateRobotStates(QString hostName, int *state, QString *address) {
    QHostInfo hostInfo = QHostInfo::fromName(hostName);
    if (hostInfo.error() == QHostInfo::NoError) {
        *state = 2;
        if (hostInfo.addresses().isEmpty()) {
            *address = "Unknown";
        } else {
            *address = hostInfo.addresses().at(0).toString();
        }
        if (checkServerConnection(hostName)) {
            *state = 3;
        }
    } else {
        *state = 1;
        *address = hostInfo.errorString();
    }
}

bool LauncherModel::checkServerConnection(QString hostName) {
    QTcpSocket cs;
    cs.connectToHost(hostName, 22);
    cs.waitForConnected(5);
    bool state = cs.state() == QTcpSocket::ConnectedState;
    cs.close();
    return state;
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
