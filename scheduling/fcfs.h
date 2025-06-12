#pragma once

#include <QString>
#include"scheduling/scheduling.h"
#include<QQueue>

class FCFS : public Scheduling<>
{
public:

    explicit FCFS(QObject* parent = nullptr) : Scheduling<>(parent){
        setName("FCFS");
    }
    ~FCFS(){}
    void pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e) override;
    void contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                          bool isNewInput, bool &running, int& startTime, int endTime) override;
    void startProcess(ProcessList::element& p,
                         QList<ReadyQueueType>& readyQueue,
                         bool& running, int& startTime, int endTime) override;
};
