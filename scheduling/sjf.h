#pragma once

#include"scheduling/scheduling.h"
#include<QQueue>
#include<queue>

struct cmp{
    bool operator()(ProcessList::element a, ProcessList::element b){
        if(a.serviceTime == b.serviceTime) return a.arrivalTime > b.arrivalTime;
        return a.serviceTime > b.serviceTime;
    }
};

using SjfPq = std::priority_queue<ProcessList::element, std::vector<ProcessList::element>, cmp>;

class SJF : public Scheduling<SjfPq>
{
public:
    explicit SJF(QObject* parent = nullptr) : Scheduling<ReadyQueueType>(parent){
        setName("SJF");
    }
    ~SJF(){ }
    void pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e) override;
    void contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                          bool isNewInput, bool &running, int& startTime, int endTime) override;
    void startProcess(ProcessList::element& p,
                         QList<ReadyQueueType>& readyQueue,
                         bool& running, int& startTime, int endTime) override;
};
