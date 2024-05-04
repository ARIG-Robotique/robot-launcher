#include <devicestate.h>

#include <QHostInfo>
#include <QTcpSocket>

DeviceState::DeviceState(QString hostName)
{
    this->hostName = hostName;
}

int DeviceState::getLastState() {
    return this->lastState;
}

QString DeviceState::getAddress() {
    return this->address;
}

void DeviceState::run() {
    int currentState = 0;
    QString tmpAddress;
    while(true) {
        QHostInfo hostInfo = QHostInfo::fromName(hostName);
        if (hostInfo.error() == QHostInfo::NoError) {
            currentState = 2;
            if (hostInfo.addresses().isEmpty()) {
                tmpAddress = "Unknown";
            } else {
                tmpAddress = hostInfo.addresses().at(0).toString();
            }
            if (this->checkServerConnection()) {
                currentState = 3;
            }
        } else {
            currentState = 1;
            tmpAddress = hostInfo.errorString();
        }

        this->lastState = currentState;
        this->address = tmpAddress;
        sleep(3);
    }
}

bool DeviceState::checkServerConnection() {
    QTcpSocket cs;
    cs.connectToHost(this->hostName, 22);
    cs.waitForConnected(1000);
    bool state = cs.state() == QTcpSocket::ConnectedState;
    cs.close();
    return state;
}
