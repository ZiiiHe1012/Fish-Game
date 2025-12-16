#include "Link.h"

Link::Link(QGraphicsItem *parent) : Character(parent) {
    playerFish = new PlayerFish(this);
}