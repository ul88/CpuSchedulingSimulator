#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include"schedulingmanager.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SchedulingManager schedulingManager;
    engine.rootContext()->setContextProperty("schedulingManager", &schedulingManager);

    // for(int i=1;i<=30;i+=5){
    //     schedulingManager.getProcessList()->append(i, 6, 7, 1, 1);
    //     schedulingManager.getProcessList()->append(i+1, 1, 1, 1, 1);
    //     schedulingManager.getProcessList()->append(i+2, 2, 3, 1, 1);
    //     schedulingManager.getProcessList()->append(i+3, 2, 1, 1, 1);
    //     schedulingManager.getProcessList()->append(i+4, 4, 5, 1, 1);
    // }

    schedulingManager.getProcessList()->append(1, 0, 30, 1, 1);
    schedulingManager.getProcessList()->append(2, 3, 18, 1, 1);
    schedulingManager.getProcessList()->append(3, 6, 9, 1, 1);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("CpuSchedulingSimulator", "Main");
    return app.exec();
}
