#pragma once
#include<QList>
#include<QString>
#include<queue>
#include<QMap>
#include"listmodel/GanttChart.h"
#include"listmodel/schedulingoutput.h"
#include"listmodel/processlist.h"
#include<QSharedPointer>

template<typename T = std::queue<ProcessList::element>>
class Scheduling
{
public:
    using ReadyQueueType = T;
    explicit Scheduling(QObject* parent = nullptr) : m_size(1){
        ganttChart = new GanttChart(parent);
        output = new SchedulingOutput(parent);
    }
    virtual ~Scheduling(){
        qDebug()<<"Scheduling 소멸자 실행";
    }

    static const int maxPriority = 10;

    void run(ProcessList* processList);

    QString getName() {return m_name;}

    GanttChart* getGanttChart() const;
    SchedulingOutput* getOutput() const;

    QMap<int, QList<ProcessList::element>> getTimeTable(const ProcessList* p);
protected:
    void setName(QString name) {m_name = name;}
    void setSize(int size) {m_size = size;}
    bool readyQueueIsEmpty(const QList<ReadyQueueType>& readyQueue);
    void end(ProcessList::element p, bool& running, int startTime, int endTime);
    virtual void pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e) = 0;
    virtual void contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                        bool isNewInput, bool &running, int& startTime, int endTime) = 0;
    virtual void startProcess(ProcessList::element& p,
                         QList<ReadyQueueType>& readyQueue,
                         bool& running, int& startTime, int endTime) = 0;

    GanttChart* ganttChart;
    SchedulingOutput* output;
private:
    QString m_name;
    int m_size;
};

#include"scheduling/scheduling.hpp"
