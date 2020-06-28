#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

class QMediaPlayer;//要在之前声明该类

class AudioPlayer : public QObject//继承
{
public:
    AudioPlayer(QObject *parent);

    void startBGM();

private:
    QMediaPlayer *m_backgroundMusic; //一个类的指针作为另一个类的成员数据
};


#endif // AUDIOPLAYER_H
