#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class attackPath;
class QPainter;
class MainWindow;
class Tower;

class Monster : public QObject//继承
{
    Q_OBJECT
public:
    Monster(attackPath *startWayPoint, MainWindow *game, const QPixmap &sprite);
    ~Monster();

    void draw(QPainter *painter) const;
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint pos() const;

public slots:
    void doActivate();

private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    qreal			m_walkingSpeed;
    qreal			m_rotationSprite;

    QPoint			m_pos;//类的组合
    attackPath *	m_destinationWayPoint;
    MainWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;

    const QPixmap	m_sprite;
    static const QSize ms_fixedSize;
};

#endif // ENEMY_H
