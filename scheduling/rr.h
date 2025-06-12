#pragma once
#include"scheduling/scheduling.h"

class RR : public Scheduling<>
{
public:
    explicit RR(QObject* parent = nullptr) : Scheduling<ReadyQueueType>(parent){
        setName("RR");
    }
    ~RR() {}

    void pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e) override;
    void contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                          bool isNewInput, bool &running, int& startTime, int endTime) override;
    void startProcess(ProcessList::element& p,
                 QList<ReadyQueueType>& readyQueue,
                 bool& running, int& startTime, int endTime) override;
};
