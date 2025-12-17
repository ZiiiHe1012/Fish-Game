#ifndef BIGFISH_H
#define BIGFISH_H

#include "Fish.h"

class BigFish : public Fish {
public:
    explicit BigFish(QGraphicsItem *parent = nullptr, bool moveRight = true);
    
    void updateMovement(qint64 deltaTime, const QPointF &playerPos, int playerSize);
    
    // 重写 boundingRect 缩小碰撞体积
    QRectF boundingRect() const override;
    
private:
    QPointF velocity;
    qint64 changeDirectionTimer{0};
    bool moveRight;  // 添加：记住初始方向
    bool facingLeft{false};  // 添加朝向标记
    qreal chaseRange{400};  // 追踪范围
    qreal chaseSpeed{0.15};  // 追踪速度
    qreal baseChaseSpeed{0.15};  // 改为基础追击速度
};

#endif