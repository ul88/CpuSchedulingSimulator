#include "listmodel/GanttChart.h"

GanttChart::GanttChart(QObject* parent) : QAbstractListModel(parent){

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
    case PCOLOR: return m_list[index.row()].pcolor;
    case PID: return m_list[index.row()].pid;
    case START: return m_list[index.row()].start;
    case END: return m_list[index.row()].end;
    }
    return "";
}
QHash<int, QByteArray> GanttChart::roleNames() const{
    static QHash<int, QByteArray> roles;
    roles[PCOLOR] = "pcolor";
    roles[PID] = "pid";
    roles[START] = "start";
    roles[END] = "end";
    return roles;
}

void GanttChart::appendEmptyElement(int start, int end){
    m_list.append({QColor("grey"), 0, start, end});
}

void GanttChart::append(QColor pcolor, int pid, int start, int end){
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    if(!m_list.empty() && m_list.back().end != start) appendEmptyElement(m_list.back().end, start);
    m_list.append({pcolor, pid, start, end});
    endInsertRows();
}

void GanttChart::append(GanttChart::element e){
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(e);
    endInsertRows();
}

void GanttChart::clear(){
    beginResetModel();
    m_list.clear();
    endResetModel();
}
