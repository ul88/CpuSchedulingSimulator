#pragma once

#include"scheduling.h"
#include<QQueue>
#include<queue>

class SJF : public Scheduling
{
public:

    SJF();
    ~SJF() override {}
    void run(ProcessList* processList) override;
private:
    struct cmp{
        bool operator()(ProcessList::element a, ProcessList::element b){
            if(a.serviceTime == b.serviceTime) return a.arrivalTime > b.arrivalTime;
            return a.serviceTime > b.serviceTime;
        }
    };
};
