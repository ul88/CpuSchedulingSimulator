#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "manager/schedulingmanager.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SchedulingManager schedulingManager;
    engine.rootContext()->setContextProperty("schedulingManager", &schedulingManager);

    schedulingManager.getProcessList()->append(1, 0, 30, 2, 2);
    schedulingManager.getProcessList()->append(2, 3, 18, 1, 2);
    schedulingManager.getProcessList()->append(3, 6, 9, 3, 2);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("CpuSchedulingSimulator", "Main");
    return app.exec();
}
