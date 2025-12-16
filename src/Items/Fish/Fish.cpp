#include "Fish.h"

Fish::Fish(QGraphicsItem *parent, const QString &pixmapPath, FishType type, int size) 
    : Item(parent, pixmapPath), type(type), size(size) {
}

void Fish::grow(int amount) {
    size += amount;
    double newScale = scale() + amount * 0.02;
    setScale(newScale);
}