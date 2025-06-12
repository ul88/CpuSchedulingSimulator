#include "scheduling/rr.h"

void RR::pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e){
    readyQueue[0].push(e);
}
void RR::contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                          bool isNewInput, bool &running, int& startTime, int endTime){
    if((endTime - startTime)%p.timeSlice) return;
    if(readyQueueIsEmpty(readyQueue)) return;
    ganttChart->append(p.pcolor, p.pid, startTime, endTime);
    output->add(p.pcolor, p.pid, startTime - p.arrivalTime, startTime - p.arrivalTime, startTime - p.arrivalTime + p.timeSlice);

    p.arrivalTime = endTime;
    p.serviceTime = p.serviceTime - p.timeSlice;
    pushReadyQueue(readyQueue, p);
    //output
    ProcessList::element next = readyQueue[0].front();
    readyQueue[0].pop();

    p = next;
    startTime = endTime;
}
void RR::startProcess(ProcessList::element& p,
             QList<ReadyQueueType>& readyQueue,
                 bool& running, int& startTime, int endTime){
    p = readyQueue[0].front(); // 준비 큐에서 가져오기
    readyQueue[0].pop();
    startTime = endTime; // 지금 실행으로 들어간 프로세스의 시작 시간 지정
    running = true;
}
