#include "attackpath.h"
#include <QColor>

attackPath::attackPath(QPoint pos)
    : m_pos(pos)
    , m_nextWayPoint(NULL)
{
}

void attackPath::setNextWayPoint(attackPath *nextPoint)
{
    m_nextWayPoint = nextPoint;
}

attackPath* attackPath::nextWayPoint() const
{
    return m_nextWayPoint;
}

const QPoint attackPath::pos() const
{
    return m_pos;
}

