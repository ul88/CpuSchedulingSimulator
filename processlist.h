#ifndef PROCESSLISTH_H
#define PROCESSLISTH_H

#include <QAbstractListModel>
#include<QColor>
#include<algorithm>

class ProcessList : public QAbstractListModel
{
    Q_OBJECT
public:
    struct element{
        QColor pcolor;
        int pid;
        int arrivalTime;
        int serviceTime;
        int priority;
        int timeSlice;
    };
    enum ProcessListEnum{
        PCOLOR = Qt::UserRole,
        PID, ARRIVAL_TIME, SERVICE_TIME, PRIORITY, TIME_SLICE
    };

    explicit ProcessList();
    int rowCount(const QModelIndex& p) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    QString enumToQStr(ProcessListEnum e) const;
    QList<ProcessList::element> getProcessList() const {return m_list;}

    QList<ProcessList::element> sort();
public slots:
    QVariantMap getElement(int index) const;
    QColor getNewColor();
    void append(QColor color, int pid, int arrivalTime, int serviceTime, int priority, int timeSlice);
    void append(int pid, int arrivalTime, int serviceTime, int priority, int timeSlice);
    void change(int index, QColor color, int pid, int arrivalTime, int serviceTime, int priority, int timeSlice);
    void remove(int pid);
private:
    QList<ProcessList::element> m_list;
    static QList<QString> m_colorList;
    unsigned int addCount;
};

#endif // PROCESSLISTH_H
