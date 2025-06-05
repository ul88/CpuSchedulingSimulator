#include "GanttChart.h"

GanttChart::GanttChart(){

}

GanttChart::~GanttChart(){
    qDebug()<<"GanttChart 소멸자 실행";
}

int GanttChart::rowCount(const QModelIndex &p) const{
    Q_UNUSED(p)
    return m_list.size();
}
QVariant GanttChart::data(const QModelIndex &index, int role) const{
    int nRow = index.row();

    if(nRow < 0) return QVariant();

    switch((GanttChartEnum)role){
    case PCOLOR:
        return m_list[index.row()].pcolor;
    case PID:
        return m_list[index.row()].pid;
    case START:
        return m_list[index.row()].start;
    case END:
        return m_list[index.row()].end;
    }
    return "";
}
QHash<int, QByteArray> GanttChart::roleNames() const{
    static QHash<int, QByteArray> roles;
    roles[(int)GanttChartEnum::PCOLOR] = "pcolor";
    roles[(int)GanttChartEnum::PID] = "pid";
    roles[(int)GanttChartEnum::START] = "start";
    roles[(int)GanttChartEnum::END] = "end";
    return roles;
}

void GanttChart::appendEmptyElement(int start, int end){
    m_list.append({QColor("grey"), 0, start, end});
}

void GanttChart::append(QColor pcolor, int pid, int start, int end){
    m_list.append({pcolor, pid, start, end});
}

void GanttChart::append(GanttChart::element e){
    m_list.append(e);
}

void GanttChart::clear(){
    m_list.clear();
}
