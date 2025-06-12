#pragma once
#include<list>
#include"scheduling/scheduling.h"
#include<limits>

class HRN : public Scheduling<std::list<ProcessList::element>>
{
public:
    explicit HRN(QObject* parent = nullptr) : Scheduling<ReadyQueueType>(parent){
        setName("HRN");
    }
    ~HRN() {}

    void pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e) override;

    void contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                          bool isNewInput, bool &running, int& startTime, int endTime) override;
    void startProcess(ProcessList::element& p,
                 QList<ReadyQueueType>& readyQueue,
                 bool& running, int& startTime, int endTime) override;
};
