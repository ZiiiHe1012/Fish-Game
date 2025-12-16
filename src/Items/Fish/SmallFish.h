#ifndef SMALLFISH_H
#define SMALLFISH_H

#include "Fish.h"

class SmallFish : public Fish {
public:
    explicit SmallFish(QGraphicsItem *parent = nullptr, bool moveRight = true);
    
    void updateMovement(qint64 deltaTime);
    
    // 重写 boundingRect 缩小碰撞体积
    QRectF boundingRect() const override;
    
private:
    QPointF velocity;
    qint64 changeDirectionTimer{0};
};

#endif