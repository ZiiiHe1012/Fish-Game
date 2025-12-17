#include "BattlefieldLevel3.h"

BattlefieldLevel3::BattlefieldLevel3(QGraphicsItem *parent) 
    : Map(parent, ":/Items/Maps/stage_background_level3.bmp") {
    
    if (pixmapItem) {
        QPixmap scaled = pixmapItem->pixmap().scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapItem->setPixmap(scaled);
    }
}

qreal BattlefieldLevel3::getFloorHeight() {
    return 360;
}