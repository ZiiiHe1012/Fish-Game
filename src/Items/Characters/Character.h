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
    
protected:
    PlayerFish *playerFish{};
    
private:
    QPointF targetPos;
    const qreal moveSpeed{0.3};
    bool facingLeft{true};  // 默认朝左
};

#endif