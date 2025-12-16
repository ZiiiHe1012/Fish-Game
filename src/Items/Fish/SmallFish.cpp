#include "SmallFish.h"
#include <QRandomGenerator>

SmallFish::SmallFish(QGraphicsItem *parent, bool moveRight) 
    : Fish(parent, 
           moveRight ? ":/Items/Fish/small_fish_right.png" : ":/Items/Fish/small_fish_left.png",
           Fish::SMALL, 3) {
    setScale(0.1);
    setZValue(5);
    
    qDebug() << "SmallFish created, moveRight:" << moveRight;  // 添加调试


    if (pixmapItem) {
        pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }
    
    auto rand = QRandomGenerator::global();
    qreal speedX = (rand->bounded(100) + 50) / 1000.0;
    
    if (moveRight) {
        velocity = QPointF(speedX, 0);
        qDebug() << "Moving right with velocity:" << speedX;  // 添加调试
    } else {
        velocity = QPointF(-speedX, 0);
        qDebug() << "Moving left with velocity:" << -speedX;  // 添加调试
    }
}

void SmallFish::updateMovement(qint64 deltaTime) {
    setPos(pos() + velocity * deltaTime);
}

QRectF SmallFish::boundingRect() const {
    if (pixmapItem) {
        QRectF rect = pixmapItem->boundingRect();
        // 缩小碰撞体积：宽度和高度各缩小到60%
        qreal shrink = 0.6;
        qreal newWidth = rect.width() * shrink;
        qreal newHeight = rect.height() * shrink;
        qreal offsetX = (rect.width() - newWidth) / 2;
        qreal offsetY = (rect.height() - newHeight) / 2;
        return QRectF(rect.x() + offsetX, rect.y() + offsetY, newWidth, newHeight);
    }
    return QRectF();
}

