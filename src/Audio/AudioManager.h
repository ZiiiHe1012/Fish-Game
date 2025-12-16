#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

class AudioManager : public QObject {
    Q_OBJECT
public:
    static AudioManager* instance();
    
    void playTitleMusic();
    void playBattleMusic();
    void playGameOverMusic();
    void playVictoryMusic();
    void stopMusic();
    
    void setVolume(qreal volume);  // 0.0 - 1.0
    
private:
    explicit AudioManager(QObject *parent = nullptr);
    void playMusic(const QString &filePath, bool loop = false, qreal volume = 0.5);    
    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;
    
    static AudioManager *m_instance;
};

#endif