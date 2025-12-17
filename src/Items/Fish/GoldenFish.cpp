#include "GoldenFish.h"
#include <QRandomGenerator>

GoldenFish::GoldenFish(QGraphicsItem *parent, bool moveRight) 
    : Fish(parent, 
           moveRight ? ":/Items/Fish/golden_fish_right.png" : ":/Items/Fish/golden_fish_left.png",
           Fish::SMALL, 1) {
    setScale(0.05);
    setZValue(5);
    facingLeft = !moveRight;

    qDebug() << "GoldenFish created, moveRight:" << moveRight;

    if (pixmapItem) {
        pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }
    
    auto rand = QRandomGenerator::global();
    qreal speedX = (rand->bounded(200) + 150) / 1000.0;  // 速度特别快
    
    if (moveRight) {
        velocity = QPointF(speedX, 0);
        qDebug() << "Moving right with velocity:" << speedX;
    } else {
        velocity = QPointF(-speedX, 0);
        qDebug() << "Moving left with velocity:" << -speedX;
    }
}

void GoldenFish::updateMovement(qint64 deltaTime) {
    if (velocity.x() < 0 && !facingLeft) {
        facingLeft = true;
        if (pixmapItem) {
            pixmapItem->setPixmap(QPixmap(":/Items/Fish/golden_fish_left.png"));
            pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
        }
    } else if (velocity.x() > 0 && facingLeft) {
        facingLeft = false;
        if (pixmapItem) {
            pixmapItem->setPixmap(QPixmap(":/Items/Fish/golden_fish_right.png"));
            pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
        }
    }

    setPos(pos() + velocity * deltaTime);
}

QRectF GoldenFish::boundingRect() const {
    if (pixmapItem) {
        QRectF rect = pixmapItem->boundingRect();
        qreal shrink = 0.5;
        qreal newWidth = rect.width() * shrink;
        qreal newHeight = rect.height() * shrink;
        qreal offsetX = (rect.width() - newWidth) / 2;
        qreal offsetY = (rect.height() - newHeight) / 2;
        return QRectF(rect.x() + offsetX, rect.y() + offsetY, newWidth, newHeight);
    }
    return QRectF();
}