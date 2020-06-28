#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "attackpath.h"
#include "monster.h"
#include "weapon.h"
#include "plistreader.h"
#include "audioplayer.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#define MouClickRegion(X, Width, Y, Height)     \
(event->x() >= (X) && event->x() <= (X) + (Width) &&  \
event->y() >= (Y) && event->y() <= (Y) + (Height))//鼠标点击区域宏

MainWindow::MainWindow(int secen,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //根据图片大小设置窗口大小
    this->setWindowTitle("减肥大作战");
    m_waves=1;
    m_playerHp=5;
    m_playrGold=500;
    m_gameEnded=false;
    m_gameWin =false;
    m_round=secen;
    m_flag=true;
    m_audioPlayer = new AudioPlayer(this);
    m_audioPlayer->startBGM();
    QHBoxLayout *blayout =new QHBoxLayout();
    QVBoxLayout *vlayout = new QVBoxLayout();
    QLabel *labelround =new QLabel("关卡:     1");
    round=new QLabel();
    QLabel *labelgold =new QLabel("微信零钱:");
    goldcount=new QLabel();
    QLabel *labelhp =new QLabel("距离体重上限/kg:");
    gameHp = new QLabel();
    startPushButton=new QPushButton(tr("开始"));

    vlayout->addSpacing(100);

    vlayout->addWidget(labelround,Qt::AlignCenter);

    QHBoxLayout *goldlayout= new QHBoxLayout();
    goldlayout->addWidget(labelgold);
    goldlayout->addWidget(goldcount);
    vlayout->addLayout(goldlayout,Qt::AlignCenter);
    QHBoxLayout *hplayout= new QHBoxLayout();
    hplayout->addWidget(labelhp);
    hplayout->addWidget(gameHp);
    vlayout->addLayout(hplayout,Qt::AlignCenter);
    vlayout->addSpacing(100);
    vlayout->addWidget(startPushButton,Qt::AlignCenter);
    vlayout->addSpacing(100);
    blayout->addWidget(ui->widget);
    blayout->addLayout(vlayout);
    ui->widget->setFixedSize(800,580);
    this->centralWidget()->setLayout(blayout);

    combox =new QComboBox(this);
    combox->addItem(QIcon("../../../../lwTowerDemo/image/tower.png"),"塔1");
    combox->addItem(QIcon("../../../../lwTowerDemo/image/tower2.png"),"塔2");
    combox->setCurrentIndex(-1);
    combox->hide();

    combox_c=new QComboBox(this);
    combox_c->addItem("upgrade");
    combox_c->addItem("sell");
    combox_c->setCurrentIndex(-1);
    combox_c->hide();
    connect(combox,SIGNAL(currentIndexChanged(int)),this,SLOT(getInform(int)));
       connect(combox_c,SIGNAL(currentIndexChanged(int)),this,SLOT(changeState(int)));
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);
    connect(startPushButton,&QPushButton::clicked,this,&MainWindow::gameStart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPosition()
{
    QPoint p1(122,100);
    QPoint p2(256,100);
    QPoint p3(390,100);
    QPoint p4(524,100);
    QPoint p5(658,100);
    QPoint p6(189,240);
    QPoint p7(323,240);
    QPoint p8(457,240);
    QPoint p9(591,240);
    QPoint p10(256,390);
    QPoint p11(390,390);
    QPoint p12(524,390);
    QPoint p13(658,390);
    QPoint p14(189,535);
    QPoint p15(323,535);
    QPoint p16(457,535);
    QPoint p17(591,535);
    QPoint p18(80,330);
    QPoint p19(80,445);
    m_towerPositionsList.push_back(p1);
    m_towerPositionsList.push_back(p2);
    m_towerPositionsList.push_back(p3);
    m_towerPositionsList.push_back(p4);
    m_towerPositionsList.push_back(p5);
    m_towerPositionsList.push_back(p6);
    m_towerPositionsList.push_back(p7);
    m_towerPositionsList.push_back(p8);
    m_towerPositionsList.push_back(p9);
    m_towerPositionsList.push_back(p10);
    m_towerPositionsList.push_back(p11);
    m_towerPositionsList.push_back(p12);
    m_towerPositionsList.push_back(p13);
    m_towerPositionsList.push_back(p14);
    m_towerPositionsList.push_back(p15);
    m_towerPositionsList.push_back(p16);
    m_towerPositionsList.push_back(p17);
    m_towerPositionsList.push_back(p18);
    m_towerPositionsList.push_back(p19);
}

void MainWindow::initPosition2()
{
    QPoint p1(210,100);
    QPoint p2(340,100);
    QPoint p3(470,100);
    QPoint p4(600,100);
    QPoint p5(140,235);
    QPoint p6(280,240);
    QPoint p7(405,240);
    QPoint p8(535,240);
    QPoint p9(665,225);
    QPoint p10(145,390);
    QPoint p11(290,438);
    QPoint p12(665,340);
    QPoint p13(405,540);
    QPoint p14(535,540);
    QPoint p15(665,540);
    QPoint p16(3,330);
    QPoint p17(3,445);
    m_towerPositionsList.push_back(p1);
    m_towerPositionsList.push_back(p2);
    m_towerPositionsList.push_back(p3);
    m_towerPositionsList.push_back(p4);
    m_towerPositionsList.push_back(p5);
    m_towerPositionsList.push_back(p6);
    m_towerPositionsList.push_back(p7);
    m_towerPositionsList.push_back(p8);
    m_towerPositionsList.push_back(p9);
    m_towerPositionsList.push_back(p10);
    m_towerPositionsList.push_back(p11);
    m_towerPositionsList.push_back(p12);
    m_towerPositionsList.push_back(p13);
    m_towerPositionsList.push_back(p14);
    m_towerPositionsList.push_back(p15);
    m_towerPositionsList.push_back(p16);
    m_towerPositionsList.push_back(p17);
}

void MainWindow::paintEvent(QPaintEvent *)
{
   QString str("");
   if(m_round==1)
   {
       str="../../../../lwTowerDemo/image/bg1.png";
   }
   else if(m_round==2)
   {
       str="../../../../lwTowerDemo/image/bg2.png";
   }
   QPixmap cachePix(str);
   QPainter cachePainter(&cachePix);


    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const Monster *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Weapon *bullet, m_bulletList)
        bullet->draw(&cachePainter);

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
    QPoint pressPos = event->pos();//选中防御塔，选择框显示
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if(it->containPoint(pressPos)&&it->hasTower())
        {
            combox_c->move(event->pos());
            combox_c->showPopup();

             m_position=&it.i->t();
             m_pos=it->centerPos();
        }
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            m_position=&it.i->t();
            combox->move(event->pos());
            combox->showPopup();
            m_pos=it->centerPos();
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


void MainWindow::getHpDamage(int damage)
{
    m_playerHp -= damage;
    if (m_playerHp <= 0)
    {
        doGameOver();
        emit sendsucessorf(0);
    }
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
            emit sendsucessorf(1);
            // m_round=2;
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
             Monster *enemy = new Monster(startWayPoint,this,temp);
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
    startPushButton->setDisabled(true);
    if(m_round==1)
    {
        initPosition();
        addWayPoints();
        initConfig();
        loadWave();
    }
    else if(m_round==2)
    {
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
        Tower *tower = new Tower(m_pos, this,1,1);
        m_towersList.push_back(tower);
        m_playrGold =m_playrGold-30;
        update();
    }
    else if(temp==1)
        {
        Tower *tower = new Tower(m_pos, this,2,1);
        m_towersList.push_back(tower);
        m_playrGold =m_playrGold-200;
        update();
      }
    combox->hide();
    combox->setCurrentIndex(-1);
    m_position->setHasTower();
}

void MainWindow::changeState(int temp)
{
    if(temp==1)
    {
       m_position->setNoTower();
       for (int i=0;i<m_towersList.count();i++) {
           if(m_towersList.at(i)->m_pos==m_pos)
           {
               m_towersList.removeAt(i);
               m_playrGold =m_playrGold+150;
               break;
           }
       }
    }
    else if(temp==0&&canBuyTower())
    {
        for (int i=0;i<m_towersList.count();i++) {
            if(m_towersList.at(i)->m_pos==m_pos&&m_towersList.at(i)->m_degree<3)
            {
                int degree=m_towersList.at(i)->m_degree;
                int type=m_towersList.at(i)->m_type;
                Tower *tw=new Tower(m_pos,this,type,++degree);
                m_towersList.replace(i,tw);
                m_playrGold =m_playrGold-300;
                break;
            }
        }
    }
    combox_c->setCurrentIndex(-1);
}



