#pragma once

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

    explicit ProcessList(QObject* parent = nullptr);
    int rowCount(const QModelIndex& p) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    QString enumToQStr(ProcessListEnum e) const;
    QList<ProcessList::element> getList() const {return m_list;}
    QList<ProcessList::element> sort();

    Q_INVOKABLE QVariantMap getElement(int index) const;
    Q_INVOKABLE QColor getNewColor();
    Q_INVOKABLE int append(QColor color, int pid, int arrivalTime, int serviceTime, int priority, int timeSlice);
    Q_INVOKABLE int append(int pid, int arrivalTime, int serviceTime, int priority, int timeSlice);
    Q_INVOKABLE int change(int index, QColor color, int pid, int arrivalTime, int serviceTime, int priority, int timeSlice);
    Q_INVOKABLE void remove(int pid);

private:
    QList<ProcessList::element> m_list;
    static QList<QString> m_colorList;
    unsigned int addCount;

    int check(int pid, int arrivalTime, int serviceTime, int priority, int timeSlice);
};
