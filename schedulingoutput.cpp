#include "schedulingoutput.h"

SchedulingOutput::SchedulingOutput() {}

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
    case RETURN_TIME: return e.returnTime;
    case PID: return pid;
    }

    return QVariant();
}
QHash<int, QByteArray> SchedulingOutput::roleNames() const{
    static QHash<int, QByteArray> ret;
    ret[WAIT_TIME] = "waitTime";
    ret[RESPONE_TIME] = "responseTime";
    ret[RETURN_TIME] = "returnTime";
    ret[PID] = "pid";
    return ret;
}

void SchedulingOutput::append(int pid, int waitTime, int responseTime, int returnTime){
    beginInsertRows(QModelIndex(), m_pidList.size(), m_pidList.size());
    if(m_map.find(pid) == m_map.end()){
        m_pidList.append(pid);
    }
    m_map[pid].waitTime = waitTime;
    m_map[pid].responseTime = responseTime;
    m_map[pid].returnTime = returnTime;
    endInsertRows();
}

QVariantMap SchedulingOutput::getAvg(){
    qDebug()<<"getAvg() 실행";
    int size = m_pidList.size();
    qreal sumWaitTime = 0.0;
    qreal sumResponseTime = 0.0;
    qreal sumReturnTime = 0.0;
    for(const auto &iter : m_pidList){
        sumWaitTime += m_map[iter].waitTime;
        sumResponseTime += m_map[iter].responseTime;
        sumReturnTime += m_map[iter].returnTime;
    }

    QVariantMap ret = QVariantMap();
    ret["avgWaitTime"] = sumWaitTime / size;
    ret["avgResponseTime"] = sumResponseTime / size;
    ret["avgReturnTime"] = sumReturnTime / size;
    return ret;
}
