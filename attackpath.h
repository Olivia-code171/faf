#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>

class attackPath
{
public:
    attackPath(QPoint pos);

    void setNextWayPoint(attackPath *nextPoint);
    attackPath* nextWayPoint() const;
    const QPoint pos() const;

private:
    const QPoint		m_pos;//类的组合，attackPath类的成员数据是另一个类(QPoint)的对象，依赖关系
    attackPath *		m_nextWayPoint;
};

#endif // WAYPOINT_H

