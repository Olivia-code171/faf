#include "audioplayer.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>

static QString dir;

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
    , m_backgroundMusic(NULL)
{
    // 创建一直播放的背景音乐
    QUrl backgroundMusicUrl = QUrl::fromLocalFile(dir + "/Users/oliviayu/Desktop/lwTowerDemo/music/BonAppetit.mp3");
    if (QFile::exists(backgroundMusicUrl.toLocalFile()))
    {
        m_backgroundMusic = new QMediaPlayer(this);
        QMediaPlaylist *backgroundMusicList = new QMediaPlaylist();
        QMediaContent media(backgroundMusicUrl);
        backgroundMusicList->addMedia(media);
        // 设置背景音乐循环播放
        backgroundMusicList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_backgroundMusic->setPlaylist(backgroundMusicList);
    }
}

void AudioPlayer::startBGM()
{
    if (m_backgroundMusic)
        m_backgroundMusic->play();
}

