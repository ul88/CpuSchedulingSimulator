#include "listmodel/schedulingoutput.h"

SchedulingOutput::SchedulingOutput(QObject* parent) : QAbstractListModel(parent) {}

int SchedulingOutput::rowCount(const QModelIndex &p) const{
    Q_UNUSED(p)
    return m_pidList.size();
}
QVariant SchedulingOutput::data(const QModelIndex& index, int role) const{
    int i = index.row();
    if(i < 0) return QVariant();

    int pid = m_pidList[i];
    if(m_map.find(pid) == m_map.end()) return QVariant();
    const element& e = m_map[pid];

    switch(role){
    case WAIT_TIME: return e.waitTime;
    case RESPONE_TIME: return e.responseTime;
    case TURN_AROUND_TIME: return e.turnAroundTime;
    case PID: return pid;
    case PCOLOR: return e.pcolor;
    }

    return QVariant();
}
QHash<int, QByteArray> SchedulingOutput::roleNames() const{
    static QHash<int, QByteArray> ret;
    ret[WAIT_TIME] = "waitTime";
    ret[RESPONE_TIME] = "responseTime";
    ret[TURN_AROUND_TIME] = "turnAroundTime";
    ret[PID] = "pid";
    ret[PCOLOR] = "pcolor";
    return ret;
}

void SchedulingOutput::add(QColor pcolor, int pid, int waitTime, int responseTime, int turnAroundTime){
    beginResetModel();
    if(m_map.find(pid) == m_map.end()){
        m_pidList.append(pid);
        m_map[pid] = {pcolor ,0, responseTime, 0}; // 응답시간은 처음 정해지면 바뀔 이유가 없으므로 고정
    }
    m_map[pid].waitTime += waitTime;
    m_map[pid].turnAroundTime += turnAroundTime;
    endResetModel();
}

QVariantMap SchedulingOutput::getAvg(){
    qDebug()<<"getAvg() 실행";
    int size = m_pidList.size();
    qreal sumWaitTime = 0.0;
    qreal sumResponseTime = 0.0;
    qreal sumTurnAroundTime = 0.0;
    for(const auto &iter : m_pidList){
        sumWaitTime += m_map[iter].waitTime;
        sumResponseTime += m_map[iter].responseTime;
        sumTurnAroundTime += m_map[iter].turnAroundTime;
    }

    QVariantMap ret = QVariantMap();
    ret["avgWaitTime"] = sumWaitTime / size;
    ret["avgResponseTime"] = sumResponseTime / size;
    ret["avgTurnAroundTime"] = sumTurnAroundTime / size;
    return ret;
}

void SchedulingOutput::clear(){
    beginResetModel();
    m_map.clear();
    m_pidList.clear();
    endResetModel();
}
