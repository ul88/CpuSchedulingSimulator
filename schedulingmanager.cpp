#include "schedulingmanager.h"
SchedulingManager::SchedulingManager() {
    m_schedulingList.append(qSharedPointerDynamicCast<Scheduling>(QSharedPointer<FCFS>(new FCFS())));
    m_schedulingList.append(qSharedPointerDynamicCast<Scheduling>(QSharedPointer<SJF>(new SJF())));
    m_processList = QSharedPointer<ProcessList>(new ProcessList());
}

void SchedulingManager::run(){
    m_processList->sort();
    for(const auto& iter : m_schedulingList){
        iter->run(m_processList.data());
    }
}

GanttChart* SchedulingManager::getGanttChart(QString name){
    for(const auto& iter : m_schedulingList){
        if(iter->getName() == name){
            return iter->getGanttChart();
        }
    }
    return nullptr;
}

SchedulingOutput* SchedulingManager::getOutput(QString name){
    for(const auto& iter : m_schedulingList){
        if(iter->getName() == name){
            qDebug()<<"check output()";
            return iter->getOutput();
        }
    }
    return nullptr;
}
