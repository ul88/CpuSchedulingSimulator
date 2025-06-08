#pragma once

#include<QAbstractListModel>

class SchedulingOutput : public QAbstractListModel
{
    Q_OBJECT
public:
    SchedulingOutput();

    struct element{
        int waitTime;
        int responseTime;
        int returnTime;
    };

    enum SchedulingOutputEnum{
        WAIT_TIME = Qt::UserRole,
        RESPONE_TIME,
        RETURN_TIME,
        PID
    };

    int rowCount(const QModelIndex &p) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void append(int pid, int waitTime, int responseTime, int returnTime);

    Q_INVOKABLE QVariantMap getAvg();

private:
    QList<int> m_pidList;
    QMap<int,element> m_map;
};
