#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Item.h"
#include "../Fish/PlayerFish.h"

class Character : public Item {
public:
    explicit Character(QGraphicsItem *parent);
    
    void setTargetPos(const QPointF &target);
    const QPointF &getTargetPos() const { return targetPos; }
    
    void updateMovement(qint64 deltaTime);
    
    int getSize() const;
    void grow(int amount);
    
    PlayerFish* getPlayerFish() const { return playerFish; }
    
    // 添加动画相关
    void playEatingAnimation();
    void updateEatingAnimation(qint64 deltaTime);
    void applyRedTint();  // 添加红色滤镜
    void updateRedTint(qint64 deltaTime);  // 更新滤镜

    void setSpeedMultiplier(qreal multiplier) { speedMultiplier = multiplier; }

protected:
    PlayerFish *playerFish{};
    
private:
    QPointF targetPos;
    qreal baseMoveSpeed{0.35};
    qreal currentMoveSpeed{0.35};
    qreal speedMultiplier{1.0};  // 速度倍数
    bool facingLeft{true};
    
    // 动画相关
    int eatAnimFrame{0};
    qint64 eatAnimTimer{0};
    bool isPlayingEatAnim{false};

    // 红色滤镜相关
    bool isRedTinted{false};
    qint64 redTintTimer{0};
};

#endif