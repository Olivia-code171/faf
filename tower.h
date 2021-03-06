#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class Monster;
class MainWindow;
class QTimer;

class Tower : QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game,int type,int degree);
    ~Tower();

    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Monster *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();
    const QPoint	m_pos;
    int m_type;//塔类型
    int m_degree;//升级状况
private slots:
    void shootWeapon();

private:
    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    double          m_rotationSprite;

    Monster *	    m_chooseEnemy;
    MainWindow *	m_game;
    QTimer *		m_fireRateTimer;
    QPixmap	        m_sprite;//类的组合，塔长啥样

    static const QSize ms_fixedSize;
};

#endif // TOWER_H
