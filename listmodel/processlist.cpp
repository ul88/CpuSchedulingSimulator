#include "listmodel/processlist.h"

QList<QString> ProcessList::m_colorList = {
    "antiquewhite", "aqua", "aquamarine", "beige",
    "bisque", "black", "blanchedalmond", "blue", "blueviolet", "brown",
    "burlywood", "cadetblue", "chartreuse", "chocolate", "coral", "cornflowerblue",
    "cornsilk", "crimson", "cyan", "darkblue", "darkcyan", "darkgoldenrod",
    "darkgray", "darkgreen", "darkgrey", "darkkhaki", "darkmagenta", "darkolivegreen",
    "darkorange", "darkorchid", "darkred", "darksalmon", "darkseagreen", "darkslateblue",
    "darkslategray", "darkslategrey", "darkturquoise", "darkviolet", "deeppink",
    "deepskyblue", "dimgray", "dimgrey", "dodgerblue", "firebrick",
    "forestgreen", "fuchsia", "gainsboro", "gold", "goldenrod", "gray",
    "green", "greenyellow", "hotpink", "indianred", "indigo", "khaki",
    "lavender", "lavenderblush", "lawngreen", "lemonchiffon", "lightblue", "lightcoral", "lightcyan",
    "lightgoldenrodyellow", "lightgray", "lightgreen", "lightgrey", "lightpink", "lightsalmon", "lightseagreen",
    "lightskyblue", "lightslategray", "lightslategrey", "lightsteelblue", "lightyellow", "lime", "limegreen",
    "linen", "magenta", "maroon", "mediumaquamarine", "mediumblue", "mediumorchid", "mediumpurple",
    "mediumseagreen", "mediumslateblue", "mediumspringgreen", "mediumturquoise", "mediumvioletred", "midnightblue",
    "mistyrose", "moccasin", "navajowhite", "navy", "oldlace", "olive", "olivedrab", "orange",
    "orangered", "orchid", "palegoldenrod", "palegreen", "paleturquoise", "palevioletred", "papayawhip",
    "peachpuff", "peru", "pink", "plum", "powderblue", "purple", "red", "rosybrown", "royalblue",
    "saddlebrown", "salmon", "sandybrown", "seagreen", "sienna", "silver", "skyblue",
    "slateblue", "slategray", "slategrey", "springgreen", "steelblue", "tan", "teal", "thistle",
    "tomato", "turquoise", "violet", "wheat", "yellow", "yellowgreen"
};

ProcessList::ProcessList(QObject* parent) : QAbstractListModel(parent), addCount(0) { }

int ProcessList::rowCount(const QModelIndex& p) const {
    Q_UNUSED(p);
    return m_list.size();
}

QVariant ProcessList::data(const QModelIndex& index, int role) const{
    int row = index.row();
    if(row < 0) return QVariant();

    switch(role){
    case PCOLOR: return m_list[row].pcolor;
    case PID: return m_list[row].pid;
    case ARRIVAL_TIME: return m_list[row].arrivalTime;
    case SERVICE_TIME: return m_list[row].serviceTime;
    case PRIORITY: return m_list[row].priority;
    case TIME_SLICE: return m_list[row].timeSlice;
    }

    return QVariant();
}

QHash<int, QByteArray> ProcessList::roleNames() const{
    static QHash<int, QByteArray> roles;
    roles[PCOLOR] = enumToQStr(PCOLOR).toUtf8();
    roles[PID] = enumToQStr(PID).toUtf8();
    roles[ARRIVAL_TIME] = enumToQStr(ARRIVAL_TIME).toUtf8();
    roles[SERVICE_TIME] = enumToQStr(SERVICE_TIME).toUtf8();
    roles[PRIORITY] = enumToQStr(PRIORITY).toUtf8();
    roles[TIME_SLICE] = enumToQStr(TIME_SLICE).toUtf8();
    return roles;
}

QString ProcessList::enumToQStr(ProcessListEnum e) const{
    switch(e){
    case PCOLOR: return "pcolor";
    case PID: return "pid";
    case ARRIVAL_TIME: return "arrivalTime";
    case SERVICE_TIME: return "serviceTime";
    case PRIORITY: return "priority";
    case TIME_SLICE: return "timeSlice";
    }
    return "";
}

QColor ProcessList::getNewColor(){
    return QColor(m_colorList[(addCount+1)%m_colorList.size()]);
}

int ProcessList::append(QColor pcolor,int pid, int arrivalTime, int serviceTime, int priority, int timeSlice){
    int ret = check(pid, arrivalTime, serviceTime, priority, timeSlice);
    if(ret) return ret;
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    addCount = (addCount + 1) % m_colorList.size();
    m_list.append({pcolor, pid, arrivalTime, serviceTime, priority, timeSlice});
    endInsertRows();
    return ret;
}

int ProcessList::append(int pid, int arrivalTime, int serviceTime, int priority, int timeSlice){
    int ret = check(pid, arrivalTime, serviceTime, priority, timeSlice);
    if(ret) return ret;
    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    addCount = (addCount + 1) % m_colorList.size();
    m_list.append({QColor(m_colorList[addCount]), pid, arrivalTime, serviceTime, priority, timeSlice});
    endInsertRows();
    return ret;
}

int ProcessList::change(int index, QColor color, int pid, int arrivalTime, int serviceTime, int priority, int timeSlice){
    int ret = check(pid, arrivalTime, serviceTime, priority, timeSlice);
    if(ret) return ret;
    beginResetModel();
    m_list[index] = {color, pid, arrivalTime, serviceTime, priority, timeSlice};
    endResetModel();
    return ret;
}

void ProcessList::remove(int pid){
    int index = -1;
    for(int i=0;i<m_list.size();i++){
        if(m_list[i].pid == pid){
            index = i;
            break;
        }
    }

    if(index == -1) qDebug()<<"알맞는 pid가 존재하지 않습니다.";
    else {
        beginRemoveRows(QModelIndex(), index, index);
        m_list.removeAt(index);
        endRemoveRows();
    }
}

QList<ProcessList::element> ProcessList::sort(){
    QList<element> list = m_list;
    std::sort(list.begin(), list.end(), [](element a, element b) -> bool {
        if(a.arrivalTime == b.arrivalTime) return a.serviceTime < b.serviceTime;
        return a.arrivalTime < b.arrivalTime;
    });
    return list;
}

QVariantMap ProcessList::getElement(int index) const{
    QVariantMap ret = QVariantMap();
    ret[enumToQStr(PCOLOR)] = m_list[index].pcolor;
    ret[enumToQStr(PID)] = m_list[index].pid;
    ret[enumToQStr(ARRIVAL_TIME)] = m_list[index].arrivalTime;
    ret[enumToQStr(SERVICE_TIME)] = m_list[index].serviceTime;
    ret[enumToQStr(PRIORITY)] = m_list[index].priority;
    ret[enumToQStr(TIME_SLICE)] = m_list[index].timeSlice;
    return ret;
}

int ProcessList::check(int pid, int arrivalTime, int serviceTime, int priority, int timeSlice){
    // pid는 중복 금지
    // pid는 1 ~ 100까지의 수
    // arrivalTime은 0~1000까지의 수
    // serviceTime은 1~1000까지의 수
    // priority는 0~10까지의 수
    // timeSlice는 1~100까지의 수
    // 비트마스킹으로 체킹
    // pid 중복금지부터 timeSlice까지 총 6개 따라서 000000의 6비트 사용
    int ret = 0;
    for(const auto& iter : m_list){
        if(iter.pid == pid){
            ret = ret | 32;
            break;
        }
    }
    if(pid <= 0 || pid > 100) ret = ret | 16;
    if(arrivalTime < 0 || arrivalTime > 1000) ret = ret | 8;
    if(serviceTime <= 0 || serviceTime > 1000) ret = ret | 4;
    if(priority < 0 || priority > 10) ret = ret | 2;
    if(timeSlice <= 0 || timeSlice > 100) ret = ret | 1;

    return ret;
}
