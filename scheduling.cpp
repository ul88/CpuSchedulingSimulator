#include "scheduling.h"

Scheduling::Scheduling() {
    ganttChart = new GanttChart();
    output = new SchedulingOutput();
}
Scheduling::~Scheduling() {
    delete ganttChart;
    delete output;
    qDebug()<<"Scheduling 소멸자 실행";
}

GanttChart* Scheduling::getGanttChart() const {
    return ganttChart;
}

SchedulingOutput* Scheduling::getOutput() const{
    return output;
}

QMap<int, QList<ProcessList::element>> Scheduling::getTimeTable(const ProcessList* p){
    QMap<int, QList<ProcessList::element>> ret;
    for(const auto& iter : p->getList()){
        ret[iter.arrivalTime].append(iter);
    }

    return ret;
}
