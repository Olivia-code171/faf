#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "attackpath.h"
#include "monster.h"
#include "weapon.h"
#include "plistreader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#define MouClickRegion(X, Width, Y, Height)     \
(event->x() >= (X) && event->x() <= (X) + (Width) &&  \
event->y() >= (Y) && event->y() <= (Y) + (Height))

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //根据图片大小设置窗口大小
    this->setWindowTitle("减肥大作战");
      this->resize(1000,580);
     m_waves=1;
    m_playerHp=5;
    m_playrGold=1000;
    m_gameEnded=false;
    m_gameWin =false;
    m_round=1;
    m_flag=true;
    QHBoxLayout *blayout =new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();
    QLabel *labelround =new QLabel("关卡:     1");
    round=new QLabel();
      QLabel *labelgold =new QLabel("金币:");
      goldcount=new QLabel();
       QLabel *labelhp =new QLabel("血量:");
       gameHp = new QLabel();
       startPushBUtton=new QPushButton(tr("开始"));
     vlayout->addSpacing(100);
    vlayout->addWidget(labelround,Qt::AlignCenter);
 //   vlayout->addWidget(round,Qt::AlignRight);
    vlayout->addSpacing(10);
    QHBoxLayout *goldlayhout= new QHBoxLayout();
    goldlayhout->addWidget(labelgold);
    goldlayhout->addWidget(goldcount);
    vlayout->addLayout(goldlayhout,Qt::AlignCenter);
    QHBoxLayout *hplayhout= new QHBoxLayout();
    hplayhout->addWidget(labelhp);
     hplayhout->addWidget(gameHp);
     vlayout->addSpacing(10);
     vlayout->addLayout(hplayhout,Qt::AlignCenter);
      vlayout->addSpacing(100);
       vlayout->addWidget(startPushBUtton,Qt::AlignCenter);
       vlayout->addSpacing(50);
      blayout->addWidget(ui->widget);
      blayout->addLayout(vlayout);
      ui->widget->setFixedSize(800,580);
        this->centralWidget()->setLayout(blayout);
   // initWaves();

    combox =new QComboBox(this);
    combox->addItem(QIcon("../../../../lwTowerDemo/image/tower.png"),"炮塔1");
    combox->addItem(QIcon("../../../../lwTowerDemo/image/tower2.png"),"炮塔2");
    combox->addItem(QIcon("../../../../lwTowerDemo/image/tower3.png"),"炮塔3");
    combox->addItem(QIcon("../../../../lwTowerDemo/image/tower4.png"),"炮塔4");
    combox->setCurrentIndex(-1);
    combox->hide();
    connect(combox,SIGNAL(currentIndexChanged(int)),this,SLOT(getInform(int)));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);
    connect(startPushBUtton,&QPushButton::clicked,this,&MainWindow::gameStart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPosition()
{
   //第一排
    QPoint p1(142,105);
     QPoint p2(309,105);
    QPoint p5(486,105);
    QPoint p7(658,105);
    //第二
    QPoint p9(612,248);
    QPoint p11(410,240);
    QPoint p12(216,240);
     //第三
    QPoint p13(100,380);
    QPoint p14(260,400);
    QPoint p15(527,402);
      //第四排
    QPoint p16(281,530);
    QPoint p17(545,530);
    m_towerPositionsList.push_back(p1);
     m_towerPositionsList.push_back(p2);
      m_towerPositionsList.push_back(p5);
       m_towerPositionsList.push_back(p7);
        m_towerPositionsList.push_back(p9);
         m_towerPositionsList.push_back(p11);
           m_towerPositionsList.push_back(p12);
           m_towerPositionsList.push_back(p13);
            m_towerPositionsList.push_back(p14);
              m_towerPositionsList.push_back(p15);
              m_towerPositionsList.push_back(p16);
               m_towerPositionsList.push_back(p17);

}

void MainWindow::initPosition2()
{
    QPoint p1(5,439);
     QPoint p2(10,326);
    QPoint p5(130,405);
    QPoint p7(160,253);
    //第二
    QPoint p9(288,245);
    QPoint p11(297,109);
    QPoint p12(427,106);
     //第三
    QPoint p13(666,203);
    QPoint p14(660,356);
    QPoint p15(316,429);
      //第四排
    QPoint p16(420,531);
 //   QPoint p17(545,530);
    m_towerPositionsList.push_back(p1);
     m_towerPositionsList.push_back(p2);
      m_towerPositionsList.push_back(p5);
       m_towerPositionsList.push_back(p7);
        m_towerPositionsList.push_back(p9);
         m_towerPositionsList.push_back(p11);
           m_towerPositionsList.push_back(p12);
           m_towerPositionsList.push_back(p13);
            m_towerPositionsList.push_back(p14);
              m_towerPositionsList.push_back(p15);
              m_towerPositionsList.push_back(p16);
           //    m_towerPositionsList.push_back(p17);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        if(m_gameEnded)
        {
            m_flag =false;
        QString text =" game over";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
        }
        else if(m_gameWin)
        {
              m_flag =false;
             // m_wayPointsList.clear();
                m_towerPositionsList.clear();
                m_towersList.clear();
                m_enemyList.clear();
                m_bulletList.clear();
                startPushBUtton->setEnabled(true);

        }
    }




   QString str("");

    if(m_round==1&&m_flag)
    {
        str="../../../../lwTowerDemo/image/bg1.png";
    }
    else if(m_round==2&&m_flag)
    {
         str="../../../../lwTowerDemo/image/bg2.png";
    }
      QPixmap cachePix(str);
     QPainter cachePainter(&cachePix);


    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

//    foreach (const attackPath *wayPoint, m_wayPointsList)
//        wayPoint->draw(&cachePainter);

    foreach (const Monster *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Weapon *bullet, m_bulletList)
        bullet->draw(&cachePainter);

//	drawWave(&cachePainter);
//	drawHP(&cachePainter);
//	drawPlayerGold(&cachePainter);
    //金币更新
   // m_waves=m_waves+1;
    goldcount->setText(QString::number(m_playrGold));
    gameHp->setText(QString::number(m_playerHp));
    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
    QPixmap result;
    if(m_playerHp==5)
    {
       result =QPixmap("../../../../lwTowerDemo/image/45kg.png");
    }
    else if(m_playerHp==4)
    {
        result =QPixmap("../../../../lwTowerDemo/image/50kg.png");
    }
    else if(m_playerHp==3)
    {
         result =QPixmap("../../../../lwTowerDemo/image/55kg.png");
    }
    else
    {
        result =QPixmap("../../../../lwTowerDemo/image/60kg.png");
    }
    painter.drawPixmap(730,420,result);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->pos();
    combox->hide();
    QPoint pressPos = event->pos();
            //选中防御塔，选择框显示

    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {

    //		m_audioPlayer->playSound(TowerPlaceSound);
            m_position=&it.i->t();
            combox->move(event->pos());
            combox->showPopup();
            m_pos=it->centerPos();
//            Tower *tower = new Tower(it->centerPos(), this);
//            m_towersList.push_back(tower);
//            update();
            break;
        }

        ++it;
    }

}

bool MainWindow::canBuyTower() const
{
    if (m_playrGold >= initGold)
        return true;
    return false;
}



void MainWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void MainWindow::initConfig()
{
    paraconfig.clear();
      QPair<QString,int> temp;
    QVector<QPair<QString,int>> round1;
     QVector<QPair<QString,int>> round2;
       QVector<QPair<QString,int>> round3;
    for (int i=0;i<5;i++) {
        temp.first="monster1";
        temp.second=(qrand()%30)*100;
        round1.append(temp);
        temp.first="monster2";
        temp.second=(10+qrand()%40)*100;
        round2.append(temp);
        temp.first="monster3";
         temp.second=(3+qrand()%3)*1000;
         round3.append(temp);
    }
    for (int i=0;i<3;i++) {
        temp.first="monster2";
        temp.second=(3+qrand()%3)*1000;
        round1.append(temp);
        round3.append(temp);
        temp.first="monster3";
        temp.second=(2+qrand()%3)*1000;
        round2.append(temp);
    }
    paraconfig.insert(1,round1);
     paraconfig.insert(2,round2);
      paraconfig.insert(3,round3);
}

void MainWindow::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}


void MainWindow::addWayPoints()
{
    attackPath *wayPoint1 = new attackPath(QPoint(730,488));
    m_wayPointsList.push_back(wayPoint1);

    attackPath *wayPoint2 = new attackPath(QPoint(194,477));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    attackPath *wayPoint3 = new attackPath(QPoint(192,348));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    attackPath *wayPoint4 = new attackPath(QPoint(705,327));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    attackPath *wayPoint5 = new attackPath(QPoint(705,197));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    attackPath *wayPoint6 = new attackPath(QPoint(50,188));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

}
void MainWindow::addWayPoints2()
{
  //  m_wayPointsList.clear();
    attackPath *wayPoint1 = new attackPath(QPoint(710,490));
    m_wayPointsList.push_back(wayPoint1);

    attackPath *wayPoint2 = new attackPath(QPoint(400,490));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    attackPath *wayPoint3 = new attackPath(QPoint(392,420));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    attackPath *wayPoint4 = new attackPath(QPoint(610,406));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    attackPath *wayPoint5 = new attackPath(QPoint(620,200));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    attackPath *wayPoint6 = new attackPath(QPoint(250,200));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);


    attackPath *wayPoint7 = new attackPath(QPoint(230,330));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    attackPath *wayPoint8 = new attackPath(QPoint(89,340));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    attackPath *wayPoint9 = new attackPath(QPoint(87,513));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

}


void MainWindow::getHpDamage(int damage/* = 1*/)
{
//	m_audioPlayer->playSound(LifeLoseSound);
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void MainWindow::removedEnemy(Monster *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        m_waves=m_waves+1;
        if (!loadWave())
        {
            m_gameWin = true;
            m_round=2;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void MainWindow::removedBullet(Weapon *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Weapon *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
    foreach (Monster *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}


bool MainWindow::loadWave()
{
   if(m_waves>=paraconfig.size())
   {
       return false;
   }
   m_waves=m_waves+1;
   qDebug()<<"waves:"<<m_waves;
     attackPath *startWayPoint = m_wayPointsList.back();
     for (int i=0;i<paraconfig.size();i++) {
         for (int j=0;j<paraconfig[i].size();j++) {
               QPixmap temp;
             if(paraconfig[i][j].first=="monster1")
             {
                  temp=QPixmap("../../../../lwTowerDemo/image/monster1.png");
             }
              else if(paraconfig[i][j].first=="monster2")
              {
                   temp=QPixmap("../../../../lwTowerDemo/image/monster2.png");
              }
              else if(paraconfig[i][j].first=="monster3")
              {
                    temp=QPixmap("../../../../lwTowerDemo/image/monster3.png");
              }
             int stime=paraconfig[i][j].second;
             Monster *enemy = new Monster(startWayPoint, this,temp);
             m_enemyList.push_back(enemy);
              QTimer::singleShot(stime, enemy, SLOT(doActivate()));
         }
     }
     return true;

}

bool MainWindow::loadWave2()
{
     m_flag=true;
    m_waves=1;
   m_playerHp=5;
   m_playrGold=2000;
   m_gameEnded=false;
   m_gameWin =false;
}

QList<Monster *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::gameStart()
{
    startPushBUtton->setDisabled(true);
    if(m_round==1)
    {
      initPosition();
     addWayPoints();
      initConfig();
    loadWave();
    }
    else if(m_round==2)
    {
        m_flag=true;
        loadWave2();
        initPosition2();
        addWayPoints2();
          initConfig();

        loadWave();
    }
}

void MainWindow::getInform(int temp)
{

    if(temp==0)
    {
        Tower *tower = new Tower(m_pos, this,QPixmap("../../../../lwTowerDemo/image/tower.png"));
        m_towersList.push_back(tower);
           m_playrGold =m_playrGold-100;
        update();
    }
    else if(temp==1)
        {
        Tower *tower = new Tower(m_pos, this,QPixmap("../../../../lwTowerDemo/image/tower2.png"));
        m_towersList.push_back(tower);
          m_playrGold =m_playrGold-200;
        update();
      }
    else if(temp==2)
    {
        Tower *tower = new Tower(m_pos, this,QPixmap("../../../../lwTowerDemo/image/tower3.png"));
        m_towersList.push_back(tower);
          m_playrGold =m_playrGold-300;
        update();
    }
    else if(temp==3)
    {
        Tower *tower = new Tower(m_pos, this,QPixmap("../../../../lwTowerDemo/image/tower4.png"));
        m_towersList.push_back(tower);
          m_playrGold =m_playrGold-400;
        update();
    }
    combox->hide();
    combox->setCurrentIndex(-1);
    m_position->setHasTower();
}
