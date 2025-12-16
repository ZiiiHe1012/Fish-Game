#include "AudioManager.h"
#include <QUrl>

AudioManager* AudioManager::m_instance = nullptr;

AudioManager::AudioManager(QObject *parent) : QObject(parent) {
    musicPlayer = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    musicPlayer->setAudioOutput(audioOutput);
    
    // 默认音量
    audioOutput->setVolume(0.5);
}

AudioManager* AudioManager::instance() {
    if (!m_instance) {
        m_instance = new AudioManager();
    }
    return m_instance;
}

void AudioManager::playMusic(const QString &filePath, bool loop, qreal volume) {    musicPlayer->stop();
    
    // 检查是否有残留的循环连接，先断开
    musicPlayer->disconnect(this);
    
    musicPlayer->setSource(QUrl(filePath));

    audioOutput->setVolume(qBound(0.0, volume, 1.0));

    if (loop) {
        // 只有当 loop 为 true 时，才设置循环播放
        connect(musicPlayer, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::EndOfMedia) {
                musicPlayer->setPosition(0);
                musicPlayer->play();
            }
        });
    }

    musicPlayer->play();
}

void AudioManager::playTitleMusic() {
    playMusic("qrc:/Music/title_bgm.mp3", true, 0.5);
}

void AudioManager::playBattleMusic() {
    playMusic("qrc:/Music/battle_bgm.mp3", true, 0.5);
}

void AudioManager::playGameOverMusic() {
    playMusic("qrc:/Music/gameover_bgm.mp3", false, 0.75);
}

void AudioManager::playVictoryMusic() {
    playMusic("qrc:/Music/victory_bgm.mp3", false, 0.75);
}

void AudioManager::stopMusic() {
    musicPlayer->stop();
}

void AudioManager::setVolume(qreal volume) {
    audioOutput->setVolume(qBound(0.0, volume, 1.0));
}