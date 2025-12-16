#include "Battlefield.h"

Battlefield::Battlefield(QGraphicsItem *parent) 
    : Map(parent, ":/Items/Maps/stage_background.bmp") {
    
    // 直接缩放图片到1280x720
    if (pixmapItem) {
        QPixmap scaled = pixmapItem->pixmap().scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        pixmapItem->setPixmap(scaled);
    }
}

qreal Battlefield::getFloorHeight() {
    return 360;  // 场景中心高度
}