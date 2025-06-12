#pragma once
#include<QMutex>
#include<QMutexLocker>
#include <QQuickItem>
#include <QList>
#include<QSharedPointer>
#include"listmodel/processlist.h"
#include"scheduling/fcfs.h"
#include"scheduling/sjf.h"
#include"scheduling/nonpreemptivepriority.h"
#include"scheduling/preemptivepriority.h"
#include"scheduling/rr.h"
#include"scheduling/hrn.h"
#include"scheduling/srt.h"
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
    Q_INVOKABLE ProcessList* getProcessList() {return m_processList;}

private:
    QMutex m_mutex;
    ProcessList* m_processList;
    FCFS fcfs = FCFS(this);
    SJF sjf = SJF(this);
    NonpreemptivePriority nonpreemptivePriority = NonpreemptivePriority(this);
    PreemptivePriority preemptivePriority = PreemptivePriority(this);
    HRN hrn = HRN(this);
    RR rr = RR(this);
    SRT srt = SRT(this);
};
