#pragma once
#include"scheduling/scheduling.h"
template<typename T>
GanttChart* Scheduling<T>::getGanttChart() const {
    return ganttChart;
}

template<typename T>
SchedulingOutput* Scheduling<T>::getOutput() const{
    return output;
}

template<typename T>
QMap<int, QList<ProcessList::element>> Scheduling<T>::getTimeTable(const ProcessList* p){
    QMap<int, QList<ProcessList::element>> ret;
    for(const auto& iter : p->getList()){
        ret[iter.arrivalTime].append(iter);
    }

    return ret;
}

template<typename T>
bool Scheduling<T>::readyQueueIsEmpty(const QList<ReadyQueueType>& readyQueue){
    for(int i=0;i<m_size;i++){
        if(!readyQueue[i].empty()) return false;
    }
    return true;
}

template<typename T>
void Scheduling<T>::end(ProcessList::element p, bool& running, int startTime, int endTime){
    running = false; // 서비스 시간이 끝났으므로 더 볼 필요가 없음
    ganttChart->append(p.pcolor, p.pid, startTime, endTime);
    output->add(p.pcolor, p.pid, startTime-p.arrivalTime, startTime - p.arrivalTime, startTime - p.arrivalTime + p.serviceTime);
}

template<typename T>
void Scheduling<T>::run(ProcessList* processList){
    qDebug()<<m_name<<" 실행";
    ganttChart->clear();
    output->clear();
    qDebug()<<"클리어 완료";
    // MLQ를 응용
    // 우선순위 별로 나누기 위해 queue 배열 생성
    // 우선순위는 0~10까지만 존재할 것 이므로 11개짜리 정적 배열 생성
    QList<ReadyQueueType> readyQueue = QList<ReadyQueueType>(m_size);

    QMap<int, QList<ProcessList::element>> timeTable = getTimeTable(processList);
    int nowTime = -1;
    int inputQueue = 0;
    bool running = false;
    int startTime = 0;
    ProcessList::element p;
    while(inputQueue < processList->getList().size() || !readyQueueIsEmpty(readyQueue) || running){
        nowTime++;
        // 만약 문맥교환이 새로운 프로세스가 들어올 때 되야할 때를 위해서
        bool isNewInput = false;

        // 현재 시간에 들어올 프로세스가 있다면 준비 큐에 삽입
        if(timeTable.contains(nowTime)){
            for(const auto& iter : timeTable[nowTime]){
                pushReadyQueue(readyQueue, iter);
                inputQueue++;
                isNewInput = true;
            }
        }

        if(running){
            if(nowTime-startTime == p.serviceTime){ // 실행이 종료되었을 때
                end(p, running, startTime, nowTime);
            }else if(nowTime - startTime > p.serviceTime){
                qDebug()<<"오류 발생 "<<m_name<< " 강제 종료";
                return;
            }else{ // 실행 중이면서 빠질 필요가 없을 때
                contextSwitching(p, readyQueue, isNewInput, running, startTime, nowTime);
            }
        }

        // 준비 큐가 비었다면, 더 이상 못봄
        if(readyQueueIsEmpty(readyQueue)) continue;
        // 실행 중이 아니면 준비 큐에서 프로세스를 가져온다.
        if(!running){
            startProcess(p, readyQueue, running, startTime, nowTime);
            output->add(p.pcolor, p.pid, 0, nowTime - p.arrivalTime, 0);
        }
    }
}
