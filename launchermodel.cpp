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
