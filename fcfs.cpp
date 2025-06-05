#include "fcfs.h"

FCFS::FCFS() {
    m_name = "FCFS";
}
FCFS::~FCFS(){}

void FCFS::run(ProcessList* processList){
    qDebug()<<"FCFS 실행";
    ganttChart->clear();
    int now = 0;
    for(auto iter : processList->sort()){
        if(now < iter.arrivalTime) now = iter.arrivalTime;
        ganttChart->append(iter.pcolor, iter.pid, now, now+iter.serviceTime);
        now += iter.serviceTime;
    }
}
