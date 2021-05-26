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
    Q_PROPERTY(QString networkInfo READ getNetworkInfo WRITE setNetworkInfo NOTIFY networkInfoChanged)

    static LauncherModel* instance;
    LauncherModel(QObject *parent = nullptr);

public:

    static QObject* singletonProvider(QQmlEngine *engine = nullptr, QJSEngine *scriptEngine = nullptr);
    static LauncherModel* getInstance();

    QString getAction();
    void setAction(QString action);

    QString getNetworkInfo();
    void setNetworkInfo(QString value);

signals:
    void actionChanged(QString newValue);
    void networkInfoChanged(QString newValue);

private:
    QString networkInfo;
};

#endif // LAUNCHERMODEL_H
