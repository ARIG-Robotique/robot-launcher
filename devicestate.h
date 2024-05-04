#ifndef DEVICESTATE_H
#define DEVICESTATE_H

#include <QThread>

class DeviceState : public QThread
{
public:
    explicit DeviceState(QString hostName);

    int getLastState();
    QString getAddress();

    void run();

private:
    QString hostName;

    int lastState = 0;
    QString address = "Refresh in progress...";

    bool checkServerConnection();
};

#endif // DEVICESTATE_H
