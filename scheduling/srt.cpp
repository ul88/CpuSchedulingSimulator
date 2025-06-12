#include "scheduling/srt.h"

void SRT::pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e){
    readyQueue[0].push(e);
}

void SRT::contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                           bool isNewInput, bool &running, int& startTime, int endTime){
    if(!isNewInput) return;

    ProcessList::element next = readyQueue[0].top();

    // 현재 프로세스보다 새로 들어온 프로세스의 서비스 시간이 더 길면 안봄
    if(next.serviceTime > p.serviceTime - endTime + startTime) return;
    // 만약 남은 시간이 같은데 다음 프로세스의 우선순위가 더 높으면 안봄
    if(next.serviceTime == p.serviceTime - endTime + startTime && next.priority > p.priority) return;
    ganttChart->append(p.pcolor, p.pid, startTime, endTime);
    output->add(p.pcolor, p.pid, startTime - p.arrivalTime, startTime - p.arrivalTime, startTime - p.arrivalTime + endTime - startTime);

    readyQueue[0].pop();

    p.arrivalTime = endTime;
    p.serviceTime -= (endTime - startTime);

    pushReadyQueue(readyQueue, p);
    p = next;
    startTime = endTime;
}
void SRT::startProcess(ProcessList::element& p,
                  QList<ReadyQueueType>& readyQueue,
                  bool& running, int& startTime, int endTime){
    p = readyQueue[0].top();
    readyQueue[0].pop(); // 준비 큐에서 가져오기
    startTime = endTime; // 지금 실행으로 들어간 프로세스의 시작 시간 지정
    running = true; // 다시 실행으로 변경
}
