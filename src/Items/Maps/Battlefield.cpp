#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem *parent) 
    : Map(parent, ":/Items/Maps/stage_background.bmp") {}

qreal Battlefield::getFloorHeight() {
    return 360;  // 简化，不再需要
}