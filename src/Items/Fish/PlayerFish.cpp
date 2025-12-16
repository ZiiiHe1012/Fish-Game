#include "PlayerFish.h"

PlayerFish::PlayerFish(QGraphicsItem *parent) 
    : Fish(parent, ":/Items/Fish/player_fish_left.png", Fish::PLAYER, 5) {
    setScale(0.2);
    setZValue(10);
}

void PlayerFish::setFacingLeft() {
    if (pixmapItem) {
        pixmapItem->setPixmap(QPixmap(":/Items/Fish/player_fish_left.png"));
    }
}

void PlayerFish::setFacingRight() {
    if (pixmapItem) {
        pixmapItem->setPixmap(QPixmap(":/Items/Fish/player_fish_right.png"));
    }
}