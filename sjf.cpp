#include "sjf.h"

SJF::SJF() {
    setName("SJF");
}

void SJF::run(ProcessList* processList){
    qDebug()<<"SJF 실행";
    ganttChart->clear();
    //Qt framework에는 우선순위 큐가 없으므로 기본 stl 사용
    std::priority_queue<ProcessList::element, std::vector<ProcessList::element>, cmp> readyQueue;
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
                readyQueue.push(iter);
                inputQueue++;
            }
        }

        if(running){
            if(nowTime-startTime == p.serviceTime){
                running = false; // 서비스 시간이 끝났으므로 더 볼 필요가 없음
                ganttChart->append(p.pcolor, p.pid, startTime, nowTime);
            }else if(nowTime - startTime > p.serviceTime){
                qDebug()<<"오류 발생 SJF 강제 종료";
                return;
            }
        }
        // 준비 큐가 비었다면, 더 이상 못봄
        if(readyQueue.empty()) continue;
        // 실행 중이 아니면 준비 큐에서 프로세스를 가져온다.
        if(!running){
            p = readyQueue.top();
            readyQueue.pop(); // 준비 큐에서 가져오기
            startTime = nowTime; // 지금 실행으로 들어간 프로세스의 시작 시간 지정
            running = true; // 다시 실행으로 변경
        }
    }
}
