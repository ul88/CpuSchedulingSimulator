#ifndef SCHEDULING_H
#define SCHEDULING_H

#include"processlist.h"
#include"GanttChart.h"
#include<QList>
#include<QString>
class Scheduling
{
public:
    explicit Scheduling();
    virtual ~Scheduling();
    QString getName() {return m_name;}
    virtual void run(ProcessList* processList) = 0; // Scheduling Class를 상속받는 class에서 구현해야할 실제 프로세스 동작
    GanttChart* getGanttChart() const;
protected:
    QString m_name;
    GanttChart* ganttChart;
};

#endif // SCHEDULING_H
