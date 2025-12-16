#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem *parent) 
    : Map(parent, ":/Items/Maps/stage_background.bmp") {
    
    if (pixmapItem) {
        QPixmap scaled = pixmapItem->pixmap().scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapItem->setPixmap(scaled);
    }
}

qreal Battlefield::getFloorHeight() {
    return 360;  // 场景中心高度
}