#ifndef BIGFISH_H
#define BIGFISH_H

#include "Fish.h"

class BigFish : public Fish {
public:
    explicit BigFish(QGraphicsItem *parent = nullptr, bool moveRight = true);
    
    void updateMovement(qint64 deltaTime, const QPointF &playerPos, int playerSize);
    
    QRectF boundingRect() const override;
    
private:
    QPointF velocity;
    qint64 changeDirectionTimer{0};
    bool moveRight;  // 初始方向
    bool facingLeft{false};  // 朝向标记
    qreal chaseRange{400};  // 追踪范围
    qreal chaseSpeed{0.15};  // 追踪速度
    qreal baseChaseSpeed{0.15};  // 基础追击速度
};

#endif