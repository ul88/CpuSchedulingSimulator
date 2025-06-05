#include "scheduling.h"

Scheduling::Scheduling() {
    ganttChart = new GanttChart;
}
Scheduling::~Scheduling() {
    delete ganttChart;
    qDebug()<<"Scheduling 소멸자 실행";
}

GanttChart* Scheduling::getGanttChart() const {
    return ganttChart;
}

QMap<int, QList<ProcessList::element>> Scheduling::getTimeTable(const ProcessList* p){
    QMap<int, QList<ProcessList::element>> ret;
    for(const auto& iter : p->getList()){
        ret[iter.arrivalTime].append(iter);
    }

    return ret;
}
