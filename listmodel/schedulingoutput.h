#pragma once

#include<QAbstractListModel>
#include<QColor>

class SchedulingOutput : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SchedulingOutput(QObject* parent = nullptr);

    struct element{
        QColor pcolor;
        int waitTime;
        int responseTime;
        int turnAroundTime;
    };

    enum SchedulingOutputEnum{
        WAIT_TIME = Qt::UserRole,
        RESPONE_TIME,
        TURN_AROUND_TIME,
        PID,
        PCOLOR
    };

    int rowCount(const QModelIndex &p) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void add(QColor pcolor, int pid, int waitTime, int responseTime, int turnAroundTime);
    void clear();
    Q_INVOKABLE QVariantMap getAvg();

private:
    QList<int> m_pidList;
    QMap<int,element> m_map;
};
