#pragma once
#include <QAbstractListModel>
#include <QQuickItem>
#include <QColor>

class GanttChart : public QAbstractListModel{
    Q_OBJECT
    QML_ELEMENT
public:
    struct element{
        QColor pcolor;
        int pid;
        int start;
        int end;
    };

    enum GanttChartEnum{
        PCOLOR = Qt::UserRole,
        PID,
        START,
        END
    };

    explicit GanttChart(QObject* parent = nullptr);
    ~GanttChart();

    int rowCount(const QModelIndex &p) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    void appendEmptyElement(int start, int end);
    void append(QColor pcolor, int pid, int start, int end);
    void clear();
private:
    QList<GanttChart::element> m_list;
};
