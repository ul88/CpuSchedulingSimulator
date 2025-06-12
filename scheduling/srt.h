#pragma once
#include"scheduling/scheduling.h"
#include"scheduling/sjf.h"

class SRT : public Scheduling<SjfPq> // sjf에서 사용한 pq 그대로 사용
{
public:
    explicit SRT(QObject* parent = nullptr) : Scheduling<ReadyQueueType>(parent){
        setName("SRT");
    }
    ~SRT() {}
    void pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e) override;
    void contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                          bool isNewInput, bool &running, int& startTime, int endTime) override;
    void startProcess(ProcessList::element& p,
                 QList<ReadyQueueType>& readyQueue,
                 bool& running, int& startTime, int endTime) override;
};
