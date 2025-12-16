#include "BigFish.h"
#include <QRandomGenerator>

BigFish::BigFish(QGraphicsItem *parent) 
    : Fish(parent, ":/Items/Fish/big_fish.png", Fish::BIG, 10) {
    setScale(0.3);
    
    // 随机初始速度（稍慢）
    auto rand = QRandomGenerator::global();
    velocity = QPointF(
        (rand->bounded(150) - 75) / 1000.0,
        (rand->bounded(150) - 75) / 1000.0
    );
}

void BigFish::updateMovement(qint64 deltaTime) {
    changeDirectionTimer += deltaTime;
    
    // 每3-6秒随机改变方向
    if (changeDirectionTimer > QRandomGenerator::global()->bounded(3000, 6000)) {
        auto rand = QRandomGenerator::global();
        velocity = QPointF(
            (rand->bounded(150) - 75) / 1000.0,
            (rand->bounded(150) - 75) / 1000.0
        );
        changeDirectionTimer = 0;
    }
    
    setPos(pos() + velocity * deltaTime);
}