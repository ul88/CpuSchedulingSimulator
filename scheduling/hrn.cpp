#include "scheduling/hrn.h"

void HRN::pushReadyQueue(QList<ReadyQueueType>& readyQueue, ProcessList::element e){
    readyQueue[0].push_back(e);
}

void HRN::contextSwitching(ProcessList::element& p, QList<ReadyQueueType>& readyQueue,
                           bool isNewInput, bool &running, int& startTime, int endTime){
    return;
}
void HRN::startProcess(ProcessList::element& p,
                   QList<ReadyQueueType>& readyQueue,
                   bool& running, int& startTime, int endTime){

    auto maxIter = readyQueue[0].begin();
    qreal maxPriority = 0.0;

    for(auto iter = readyQueue[0].begin(); iter != readyQueue[0].end();iter++){
        qreal temp = (qreal)(endTime-iter->arrivalTime + iter->serviceTime) / iter->serviceTime; // HRN 우선순위 계산
        if(temp > maxPriority){ // temp가 더 크면 갱신
            maxPriority = temp;
            maxIter = iter;
        }
    }

    p = *maxIter; // 프로세스 추가
    readyQueue[0].erase(maxIter); // 연결리스트에서 삭제
    startTime = endTime; // 지금 실행으로 들어간 프로세스의 시작 시간 지정
    running = true;
}
