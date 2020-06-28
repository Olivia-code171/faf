#include <QApplication>
#include <startscene.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startscene *w=new startscene;
    w->show();
    return a.exec();
}

