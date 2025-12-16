#include "Character.h"
#include <QTransform>
#include <QtMath>

Character::Character(QGraphicsItem *parent) : Item(parent, "") {
    targetPos = pos();
}

void Character::setTargetPos(const QPointF &target) {
    targetPos = target;
}

void Character::updateMovement(qint64 deltaTime) {
    QPointF currentPos = pos();
    QPointF direction = targetPos - currentPos;
    qreal distance = qSqrt(direction.x() * direction.x() + direction.y() * direction.y());
    
    // 如果距离目标很近就停止移动
    if (distance < 2) {
        return;
    }
    
    // 归一化方向向量
    direction /= distance;
    
    // 根据方向切换图片
    if (direction.x() < 0 && !facingLeft) {
        // 需要朝左
        facingLeft = true;
        if (playerFish) {
            playerFish->setFacingLeft();
        }
    } else if (direction.x() > 0 && facingLeft) {
        // 需要朝右
        facingLeft = false;
        if (playerFish) {
            playerFish->setFacingRight();
        }
    }
    
    // 移动
    QPointF velocity = direction * currentMoveSpeed;
    setPos(currentPos + velocity * deltaTime);
}

int Character::getSize() const {
    if (playerFish) {
        return playerFish->getSize();
    }
    return 0;
}

void Character::grow(int amount) {
    if (playerFish) {
        playerFish->grow(amount);
        
        // 确保碰撞模式不变
        if (playerFish->getPixmapItem()) {
            playerFish->getPixmapItem()->setShapeMode(QGraphicsPixmapItem::MaskShape);
        }
        
        // 长大后速度变慢
        currentMoveSpeed = baseMoveSpeed * qPow(0.98, playerFish->getSize() - 5);
        
        if (currentMoveSpeed < 0.1) {
            currentMoveSpeed = 0.1;
        }
    }
}