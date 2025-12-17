#include "PlayerFish.h"

PlayerFish::PlayerFish(QGraphicsItem *parent) 
    : Fish(parent, ":/Items/Fish/player_fish_left.png", Fish::PLAYER, 5) {
    setScale(0.2);
    setZValue(10);

    if (pixmapItem) {
        pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }
}

void PlayerFish::setFacingLeft() {
    if (pixmapItem) {
        pixmapItem->setPixmap(QPixmap(":/Items/Fish/player_fish_left.png"));
        pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }
}

void PlayerFish::setFacingRight() {
    if (pixmapItem) {
        pixmapItem->setPixmap(QPixmap(":/Items/Fish/player_fish_right.png"));
        pixmapItem->setShapeMode(QGraphicsPixmapItem::MaskShape);
    }
}

QRectF PlayerFish::boundingRect() const {
    if (pixmapItem) {
        QRectF rect = pixmapItem->boundingRect();
        qreal shrink = 0.7;
        qreal newWidth = rect.width() * shrink;
        qreal newHeight = rect.height() * shrink;
        qreal offsetX = (rect.width() - newWidth) / 2;
        qreal offsetY = (rect.height() - newHeight) / 2;
        return QRectF(rect.x() + offsetX, rect.y() + offsetY, newWidth, newHeight);
    }
    return QRectF();
}