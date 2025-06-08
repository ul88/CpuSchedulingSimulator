#ifndef SCHEDULING_H
#define SCHEDULING_H

#include"processlist.h"
#include"GanttChart.h"
#include"schedulingoutput.h"
#include<QList>
#include<QString>
#include<QMap>
class Scheduling
{
public:
    explicit Scheduling();
    virtual ~Scheduling();
    QString getName() {return m_name;}
    virtual void run(ProcessList* processList) = 0; // Scheduling Class를 상속받는 class에서 구현해야할 실제 프로세스 동작
    GanttChart* getGanttChart() const;
    SchedulingOutput* getOutput() const;

    QMap<int, QList<ProcessList::element>> getTimeTable(const ProcessList* p);
protected:
    void setName(QString name) {m_name = name;}
    GanttChart* ganttChart;
    SchedulingOutput* output;
private:
    QString m_name;
};

#endif // SCHEDULING_H
