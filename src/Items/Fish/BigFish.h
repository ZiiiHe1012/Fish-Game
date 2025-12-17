#ifndef BIGFISH_H
#define BIGFISH_H

#include "Fish.h"

class BigFish : public Fish {
public:
    explicit BigFish(QGraphicsItem *parent = nullptr, bool moveRight = true);
    
    void updateMovement(qint64 deltaTime, const QPointF &playerPos);  // 修改这里：添加玩家位置参数
    
    // 重写 boundingRect 缩小碰撞体积
    QRectF boundingRect() const override;
    
private:
    QPointF velocity;
    qint64 changeDirectionTimer{0};
    bool moveRight;  // 添加：记住初始方向
    qreal chaseRange{300};  // 追踪范围
    qreal chaseSpeed{0.15};  // 追踪速度
};

#endif