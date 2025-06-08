#include "fcfs.h"

FCFS::FCFS() {
    setName("FCFS");
}
FCFS::~FCFS(){}

void FCFS::run(ProcessList* processList){
    qDebug()<<"FCFS 실행";
    ganttChart->clear();
    QQueue<ProcessList::element> readyQueue;
    QMap<int, QList<ProcessList::element>> timeTable = getTimeTable(processList);


    int nowTime = -1;
    int inputQueue = 0;
    bool running = false;
    int startTime = 0;
    ProcessList::element p;
    while(inputQueue < processList->getList().size() || !readyQueue.empty() || running){
        nowTime++;
        // 현재 시간에 들어올 프로세스가 있다면 준비 큐에 삽입
        if(timeTable.contains(nowTime)){
            for(const auto& iter : timeTable[nowTime]){
                readyQueue.enqueue(iter);
                inputQueue++;
            }
        }

        if(running){
            if(nowTime-startTime == p.serviceTime){
                running = false; // 서비스 시간이 끝났으므로 더 볼 필요가 없음
                ganttChart->append(p.pcolor, p.pid, startTime, nowTime);
                output->append(p.pid, startTime-p.arrivalTime, startTime-p.arrivalTime, startTime - p.arrivalTime + p.serviceTime);
            }else if(nowTime - startTime > p.serviceTime){
                qDebug()<<"오류 발생 FCFS 강제 종료";
                return;
            }
        }
        // 준비 큐가 비었다면, 더 이상 못봄
        if(readyQueue.empty()) continue;
        // 실행 중이 아니면 준비 큐에서 프로세스를 가져온다.
        if(!running){
            p = readyQueue.dequeue(); // 준비 큐에서 가져오기
            startTime = nowTime; // 지금 실행으로 들어간 프로세스의 시작 시간 지정
            running = true; // 다시 실행으로 변경
        }
    }
}
