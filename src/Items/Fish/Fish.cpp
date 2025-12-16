#include "Fish.h"

Fish::Fish(QGraphicsItem *parent, const QString &pixmapPath, FishType type, int size) 
    : Item(parent, pixmapPath), type(type), size(size) {
}

void Fish::grow(int amount) {
    size += amount;
    // 每成长1次，缩放增加3%
    double newScale = scale() * (1.0 + amount * 0.03);
    setScale(newScale);
}