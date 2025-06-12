#pragma once
#include"scheduling/scheduling.h"
#include<queue>

class NonpreemptivePriority : public Scheduling<>
{
public:
    explicit NonpreemptivePriority(QObject* parent = nullptr) : Scheduling<ReadyQueueType>(parent){
        setName("NonpreemptivePriority");
        setSize(maxPriority+1); // 0~10까지를 우선순위로 쓰기 위해서
    }
    ~NonpreemptivePriority() {}
    void pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e) override;
    void contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                          bool isNewInput, bool &running, int& startTime, int endTime) override;
    void startProcess(ProcessList::element& p,
                 QList<ReadyQueueType>& readyQueue,
                 bool& running, int& startTime, int endTime) override;
};
