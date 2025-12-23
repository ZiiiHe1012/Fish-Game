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
    void playEatSound(); 
    void playHurtSound();  
    void stopMusic();
    
    void setVolume(qreal volume);
    
private:
    explicit AudioManager(QObject *parent = nullptr);
    void playMusic(const QString &filePath, bool loop = false, qreal volume = 0.5);    
    QMediaPlayer *musicPlayer;
    QAudioOutput *audioOutput;
    
    static AudioManager *m_instance;
};

#endif