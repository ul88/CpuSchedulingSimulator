#ifndef SCHEDULINGMANAGER_H
#define SCHEDULINGMANAGER_H

#include <QQuickItem>
#include <QList>
#include<QQmlListProperty>
#include"processlist.h"
#include<QSharedPointer>
#include"fcfs.h"
class SchedulingManager : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit SchedulingManager();
    ~SchedulingManager() {}
public slots:
    void run();
    GanttChart* getGanttChart(QString name);
    ProcessList* getProcessList() {return m_processList.get();}
signals:
    void processListChanged();
private:
    QSharedPointer<ProcessList> m_processList;
    QList<QSharedPointer<Scheduling>>m_schedulingList;
};

#endif // SCHEDULINGMANAGER_H
