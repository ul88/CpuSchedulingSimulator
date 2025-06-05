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
