#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

#include <QObject>
#include <QSet>

class GameProgress : public QObject {
    Q_OBJECT
public:
    static GameProgress* instance();
    
    // 关卡通关
    void completeLevel(int level);
    bool isLevelCompleted(int level) const;
    QSet<int> getCompletedLevels() const { return completedLevels; }
    
    // 道具效果
    bool hasSharkFin() const;      // 鲨鱼鳍（速度+25%）
    bool hasPendant() const;       // 挂坠（血量150）
    
    qreal getSpeedMultiplier() const;  // 获取速度倍数
    int getMaxHealth() const;          // 获取最大血量
    
    void reset();  // 重置进度
    
private:
    explicit GameProgress(QObject *parent = nullptr);
    static GameProgress *m_instance;
    
    QSet<int> completedLevels;  // 已通关的关卡
};

#endif