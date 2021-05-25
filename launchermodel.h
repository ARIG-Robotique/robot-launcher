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
    Q_PROPERTY(QString ipAddress READ getIpAddress NOTIFY ipAddressChanged)

    static LauncherModel* instance;
    LauncherModel(QObject *parent = nullptr);

public:

    static QObject* singletonProvider(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr);
    static LauncherModel* getInstance();

    QString getAction();
    void setAction(QString action);

    QString getIpAddress();

signals:
    void actionChanged(QString newValue);
    void ipAddressChanged();

private:
    QString ipAddress;
};

#endif // LAUNCHERMODEL_H
