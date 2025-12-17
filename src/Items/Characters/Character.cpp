#include "Character.h"
#include <QTransform>
#include <QtMath>
#include <QGraphicsColorizeEffect>

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
    
    if (distance < 2) {
        return;
    }
    
    direction /= distance;
    
    if (direction.x() < 0 && !facingLeft) {
        facingLeft = true;
        if (playerFish) {
            playerFish->setFacingLeft();
        }
    } else if (direction.x() > 0 && facingLeft) {
        facingLeft = false;
        if (playerFish) {
            playerFish->setFacingRight();
        }
    }
    
    QPointF velocity = direction * currentMoveSpeed * speedMultiplier;
    setPos(currentPos + velocity * deltaTime);
    
    // 更新吃鱼动画
    updateEatingAnimation(deltaTime);
    updateRedTint(deltaTime);
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
        
        if (playerFish->getPixmapItem()) {
            playerFish->getPixmapItem()->setShapeMode(QGraphicsPixmapItem::MaskShape);
        }
        
        currentMoveSpeed = baseMoveSpeed * qPow(0.98, playerFish->getSize() - 5);
        
        if (currentMoveSpeed < 0.1) {
            currentMoveSpeed = 0.1;
        }
    }
}

void Character::playEatingAnimation() {
    isPlayingEatAnim = true;
    eatAnimFrame = 1;
    eatAnimTimer = 0;
}

void Character::updateEatingAnimation(qint64 deltaTime) {
    if (!isPlayingEatAnim || !playerFish || !playerFish->getPixmapItem()) {
        return;
    }
    
    eatAnimTimer += deltaTime;
    
    // 每150ms切换一帧
    if (eatAnimTimer >= 50) {
        eatAnimTimer = 0;
        
        // 根据朝向加载对应帧
        QString framePath;
        if (facingLeft) {
            framePath = QString(":/Items/Fish/player_fish_left_%1.png").arg(eatAnimFrame + 1);
        } else {
            framePath = QString(":/Items/Fish/player_fish_right_%1.png").arg(eatAnimFrame + 1);
        }
        
        playerFish->getPixmapItem()->setPixmap(QPixmap(framePath));
        playerFish->getPixmapItem()->setShapeMode(QGraphicsPixmapItem::MaskShape);
        
        eatAnimFrame++;
        
        // 播放完7帧后结束
        if (eatAnimFrame >= 7) {
            isPlayingEatAnim = false;
            eatAnimFrame = 0;
            
            // 恢复静态图
            if (facingLeft) {
                playerFish->setFacingLeft();
            } else {
                playerFish->setFacingRight();
            }
        }
    }
}

void Character::applyRedTint() {
    isRedTinted = true;
    redTintTimer = 500;  // 持续500ms
    
    if (playerFish && playerFish->getPixmapItem()) {
        // 应用红色滤镜
        QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
        effect->setColor(Qt::red);
        effect->setStrength(0.8);
        playerFish->getPixmapItem()->setGraphicsEffect(effect);
    }
}

void Character::updateRedTint(qint64 deltaTime) {
    if (!isRedTinted) return;
    
    redTintTimer -= deltaTime;
    
    if (redTintTimer <= 0) {
        isRedTinted = false;
        
        // 移除红色滤镜
        if (playerFish && playerFish->getPixmapItem()) {
            playerFish->getPixmapItem()->setGraphicsEffect(nullptr);
        }
    }
}