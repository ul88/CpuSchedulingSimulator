#include "manager/schedulingmanager.h"
SchedulingManager::SchedulingManager() {
    m_processList = new ProcessList();
}

void SchedulingManager::run(){
    QMutexLocker locker(&m_mutex);
    m_processList->sort();
    fcfs.run(m_processList);
    sjf.run(m_processList);
    nonpreemptivePriority.run(m_processList);
    preemptivePriority.run(m_processList);
    hrn.run(m_processList);
    rr.run(m_processList);
    srt.run(m_processList);
}

GanttChart* SchedulingManager::getGanttChart(QString name){
    QMutexLocker locker(&m_mutex);
    if(name == "FCFS") return fcfs.getGanttChart();
    if(name == "SJF") return sjf.getGanttChart();
    if(name == "NonpreemptivePriority") return nonpreemptivePriority.getGanttChart();
    if(name == "PreemptivePriority") return preemptivePriority.getGanttChart();
    if(name == "HRN") return hrn.getGanttChart();
    if(name == "RR") return rr.getGanttChart();
    if(name == "SRT") return srt.getGanttChart();
    return nullptr;
}

SchedulingOutput* SchedulingManager::getOutput(QString name){
    QMutexLocker locker(&m_mutex);
    if(name == "FCFS") return fcfs.getOutput();
    if(name == "SJF") return sjf.getOutput();
    if(name == "NonpreemptivePriority") return nonpreemptivePriority.getOutput();
    if(name == "PreemptivePriority") return preemptivePriority.getOutput();
    if(name == "HRN") return hrn.getOutput();
    if(name == "RR") return rr.getOutput();
    if(name == "SRT") return srt.getOutput();
    return nullptr;
}
