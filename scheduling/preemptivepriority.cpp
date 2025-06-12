#include "scheduling/preemptivepriority.h"

void PreemptivePriority::pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e){
    readyQueue[e.priority].push(e);
}

void PreemptivePriority::contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                                          bool isNewInput, bool &running, int& startTime, int endTime){
    if(!isNewInput) return;
    int priority = -1;
    for(int i=0;i<=maxPriority;i++){
        if(readyQueue[i].empty()) continue;
        if(p.priority > i){
            priority = i;
            break;
        }
    }
    if(priority == -1) return;

    ganttChart->append(p.pcolor, p.pid, startTime, endTime);
    output->add(p.pcolor, p.pid, startTime - p.arrivalTime, startTime - p.arrivalTime, startTime - p.arrivalTime + endTime - startTime);

    ProcessList::element next = readyQueue[priority].front();
    readyQueue[priority].pop();
    p.serviceTime -= (endTime - startTime);
    p.arrivalTime = endTime;

    pushReadyQueue(readyQueue, p);

    p = next;
    startTime = endTime;
}

void PreemptivePriority::startProcess(ProcessList::element& p,
                                    QList<ReadyQueueType>& readyQueue,
                                    bool& running, int& startTime, int endTime){
    for(int i=0;i<=maxPriority;i++){
        if(readyQueue[i].empty()) continue; // i에 해당하는 우선순위 준비큐에 아무것도 없다면 다음 우선순위를 봄
        p = readyQueue[i].front(); // 우선순위가 가장 빠른 큐에서 가져옴
        readyQueue[i].pop(); // 우선순위가 가장 빠른 큐에서 삭제
        break;
    }
    startTime = endTime; // 지금 실행으로 들어간 프로세스의 시작 시간 지정
    running = true; // 다시 실행으로 변경
}
