#include "SmallFish.h"
#include <QRandomGenerator>

SmallFish::SmallFish(QGraphicsItem *parent) 
    : Fish(parent, ":/Items/Fish/small_fish.png", Fish::SMALL, 3) {
    setScale(0.1);
    
    // 随机初始速度
    auto rand = QRandomGenerator::global();
    velocity = QPointF(
        (rand->bounded(200) - 100) / 1000.0,
        (rand->bounded(200) - 100) / 1000.0
    );
}

void SmallFish::updateMovement(qint64 deltaTime) {
    changeDirectionTimer += deltaTime;
    
    // 每2-5秒随机改变方向
    if (changeDirectionTimer > QRandomGenerator::global()->bounded(2000, 5000)) {
        auto rand = QRandomGenerator::global();
        velocity = QPointF(
            (rand->bounded(200) - 100) / 1000.0,
            (rand->bounded(200) - 100) / 1000.0
        );
        changeDirectionTimer = 0;
    }
    
    setPos(pos() + velocity * deltaTime);
}