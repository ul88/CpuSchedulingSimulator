#include "scheduling/sjf.h"

void SJF::pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e){
    readyQueue[0].push(e);
}

void SJF::contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                           bool isNewInput, bool &running, int& startTime, int endTime){
    return;
}
void SJF::startProcess(ProcessList::element& p,
                QList<ReadyQueueType>& readyQueue,
                  bool& running, int& startTime, int endTime){
    p = readyQueue[0].top();
    readyQueue[0].pop(); // 준비 큐에서 가져오기
    startTime = endTime; // 지금 실행으로 들어간 프로세스의 시작 시간 지정
    running = true; // 다시 실행으로 변경
}
