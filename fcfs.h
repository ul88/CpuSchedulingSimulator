#ifndef FCFS_H
#define FCFS_H

#include <QString>
#include"scheduling.h"

class FCFS : public Scheduling
{
public:
    explicit FCFS();
    ~FCFS() override;
    void run(ProcessList* processList) override;
};

#endif // FCFS_H
