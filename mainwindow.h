#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMap>
#include <QVector>
#include <QPair>
#include <QComboBox>
#include <QMediaPlayer>
#include "towerposition.h"
#include "tower.h"
#include "weapon.h"
#include "attackpath.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class AudioPlayer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int secen,QWidget *parent = nullptr);
    ~MainWindow();
    AudioPlayer* audioPlayer() const;
public:
    void getHpDamage(int damage = 1);
    void removedEnemy(Monster *enemy);
    void removedBullet(Weapon *bullet);
    void addBullet(Weapon *bullet);
    void awardGold(int gold);
    QList<Monster *> enemyList() const;

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
signals:
    void sendsucessorf(int);
public slots:
    void updateMap();
    void gameStart();
    void getInform(int);
    void changeState(int);
private:
    QMap<int,QVector<QPair<QString,int>>> paraconfig;
    const int initGold =300;
    QPushButton *startPushButton;
    QComboBox *combox;
      QComboBox *combox_c;
    bool m_flag;
     TowerPosition* m_position;
   QLabel *round;
   int m_round;
   QLabel *goldcount;
   QLabel*gameHp;
   void initPosition();
    void initPosition2();
   void addWayPoints();
    void addWayPoints2();
   bool loadWave();
    bool loadWave2();
   bool canBuyTower() const;
   void doGameOver();
   void initConfig();

   QPoint m_pos;
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    bool					m_gameEnded;
    bool					m_gameWin;
    AudioPlayer *			m_audioPlayer;//类的组合
    QList<QVariant>			m_wavesInfo;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<attackPath *>		m_wayPointsList;
    QList<Monster *>		m_enemyList;
    QList<Weapon *>			m_bulletList;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
