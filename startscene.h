#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QWidget>
#include <QObject>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include "mainwindow.h"
class QPalette;
//继承
class startscene : public QWidget
{
    Q_OBJECT
public:
    startscene();
    MainWindow *w;
    QPushButton *pbtn2;
public slots:
    void getsuccessorfail(int);
};

#endif // STARTSCENE_H
