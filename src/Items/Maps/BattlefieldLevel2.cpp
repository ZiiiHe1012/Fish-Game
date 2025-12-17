#include "BattlefieldLevel2.h"

BattlefieldLevel2::BattlefieldLevel2(QGraphicsItem *parent) 
    : Map(parent, ":/Items/Maps/stage_background_level2.bmp") {
    
    if (pixmapItem) {
        QPixmap scaled = pixmapItem->pixmap().scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapItem->setPixmap(scaled);
    }
}

qreal BattlefieldLevel2::getFloorHeight() {
    return 360;
}