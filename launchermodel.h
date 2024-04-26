#ifndef LAUNCHERMODEL_H
#define LAUNCHERMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QGuiApplication>
#include <QFile>
#include <QString>

class LauncherModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString action READ getAction WRITE setAction NOTIFY actionChanged)

    // Read only property from QML
    Q_PROPERTY(QString networkInfo READ getNetworkInfo NOTIFY networkInfoChanged)
    Q_PROPERTY(int nerellState READ getNerellState NOTIFY nerellStateChanged)
    Q_PROPERTY(QString nerellAddress READ getNerellAddress NOTIFY nerellAddressChanged)
    Q_PROPERTY(int overlordState READ getOverlordState NOTIFY overlordStateChanged)
    Q_PROPERTY(QString overlordAddress READ getOverlordAddress NOTIFY overlordAddressChanged)
    Q_PROPERTY(int triangleState READ getTriangleState NOTIFY triangleStateChanged)
    Q_PROPERTY(QString triangleAddress READ getTriangleAddress NOTIFY triangleAddressChanged)
    Q_PROPERTY(int carreState READ getCarreState NOTIFY carreStateChanged)
    Q_PROPERTY(QString carreAddress READ getCarreAddress NOTIFY carreAddressChanged)
    Q_PROPERTY(int rondState READ getRondState NOTIFY rondStateChanged)
    Q_PROPERTY(QString rondAddress READ getRondAddress NOTIFY rondAddressChanged)

    static LauncherModel* instance;
    LauncherModel(QObject *parent = nullptr);

public:

    static QObject* singletonProvider(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr);
    static LauncherModel* getInstance();

    Q_INVOKABLE
    void refresh();

    QString getNetworkInfo();

    QString getAction();
    void setAction(QString action);

    int getNerellState();
    QString getNerellAddress();

    int getOverlordState();
    QString getOverlordAddress();

    int getTriangleState();
    QString getTriangleAddress();

    int getCarreState();
    QString getCarreAddress();

    int getRondState();
    QString getRondAddress();

signals:
    void actionChanged(QString newValue);
    void networkInfoChanged(QString newValue);
    void nerellStateChanged(int newValue);
    void nerellAddressChanged(QString newValue);
    void overlordStateChanged(int newValue);
    void overlordAddressChanged(QString newValue);
    void triangleStateChanged(int newValue);
    void triangleAddressChanged(QString newValue);
    void carreStateChanged(int newValue);
    void carreAddressChanged(QString newValue);
    void rondStateChanged(int newValue);
    void rondAddressChanged(QString newValue);

private:
    void updateRobotStates(QString hostName, int *state, QString *address);
    bool checkServerConnection(QString hostName);

    QString networkInfo = "Refresh in progress...";

    int nerellState = 0;
    QString nerellAddress = "Refresh in progress...";

    int overlordState = 0;
    QString overlordAddress = "Refresh in progress...";

    int triangleState = 0;
    QString triangleAddress = "Refresh in progress...";

    int carreState = 0;
    QString carreAddress = "Refresh in progress...";

    int rondState = 0;
    QString rondAddress = "Refresh in progress...";
};

#endif // LAUNCHERMODEL_H
