#include "BigFish.h"
#include <QRandomGenerator>

BigFish::BigFish(QGraphicsItem *parent, bool moveRight) 
    : Fish(parent, 
           moveRight ? ":/Items/Fish/big_fish_right.png" : ":/Items/Fish/big_fis_left.png",
           Fish::BIG, 10) {
    setScale(0.3);
    setZValue(5);
    
    qDebug() << "BigFish created, moveRight:" << moveRight;  // 添加调试


    if (pixmapItem) {
        pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }
    
    auto rand = QRandomGenerator::global();
    qreal speedX = (rand->bounded(80) + 40) / 1000.0;
    
    if (moveRight) {
        velocity = QPointF(speedX, 0);
        qDebug() << "Moving right with velocity:" << speedX;  // 添加调试
    } else {
        velocity = QPointF(-speedX, 0);
        qDebug() << "Moving left with velocity:" << -speedX;  // 添加调试
    }
}

void BigFish::updateMovement(qint64 deltaTime) {
    setPos(pos() + velocity * deltaTime);
}

QRectF BigFish::boundingRect() const {
    if (pixmapItem) {
        QRectF rect = pixmapItem->boundingRect();
        // 缩小碰撞体积：宽度和高度各缩小到70%
        qreal shrink = 0.7;
        qreal newWidth = rect.width() * shrink;
        qreal newHeight = rect.height() * shrink;
        qreal offsetX = (rect.width() - newWidth) / 2;
        qreal offsetY = (rect.height() - newHeight) / 2;
        return QRectF(rect.x() + offsetX, rect.y() + offsetY, newWidth, newHeight);
    }
    return QRectF();
}