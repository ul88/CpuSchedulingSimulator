#ifndef SCHEDULINGMANAGER_H
#define SCHEDULINGMANAGER_H

#include <QQuickItem>
#include <QList>
#include<QQmlListProperty>
#include"processlist.h"
#include<QSharedPointer>
#include"fcfs.h"
#include"sjf.h"
class SchedulingManager : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit SchedulingManager();
    ~SchedulingManager() {}

    Q_INVOKABLE void run();
    Q_INVOKABLE GanttChart* getGanttChart(QString name);
    Q_INVOKABLE SchedulingOutput* getOutput(QString name);
    Q_INVOKABLE ProcessList* getProcessList() {return m_processList.get();}

private:
    QSharedPointer<ProcessList> m_processList;
    QList<QSharedPointer<Scheduling>>m_schedulingList;
};

#endif // SCHEDULINGMANAGER_H
