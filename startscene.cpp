#include "startscene.h"

startscene::startscene()
{
    this->setFixedSize(800,600);
    this->setAutoFillBackground(true);
    QPalette palette;
    QPixmap pixmap("../../../../lwTowerDemo/image/login.png");palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);
    QPushButton *pbtn1=new QPushButton();
    pbtn2 =new QPushButton();
    pbtn1->setFixedSize(200,100);
    pbtn2->setFixedSize(QSize(200,100));
    pbtn1->setStyleSheet("border-image:url(../../../../lwTowerDemo/image/button1.png)");
    pbtn2->setStyleSheet("border-image:url(../../../../lwTowerDemo/image/button2.png)");

    pbtn1->move(50,360);
    pbtn2->move(50,460);
    pbtn1->setParent(this);
    pbtn2->setParent(this);
    pbtn2->setDisabled(true);
    connect(pbtn1,&QPushButton::clicked,this,[=]
    {
        this->hide();
        w=new MainWindow(1);
        connect(w,&MainWindow::sendsucessorf,this,&startscene::getsuccessorfail);
        w->show();
    });
    connect(pbtn2,&QPushButton::clicked,this,[=]{
        this->hide();
        w=new MainWindow(2);
        connect(w,&MainWindow::sendsucessorf,this,&startscene::getsuccessorfail);
        w->show();
    });
}

void startscene::getsuccessorfail(int temp)
{
    if(temp)
    {
        QMessageBox::warning(this,"Congrats!", "You haven't gained a pound!");
        pbtn2->setDisabled(false);
        w->close();
        delete w;
        this->show();

    }
    else
    {
        QMessageBox::warning(this,"","Too fat!");
        w->close();
        delete w;
        this->show();
    }
}

