#include "UIButton.h"
#include <QCursor>

UIButton::UIButton(const QString &imagePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(imagePath));
    setCursor(QCursor(Qt::PointingHandCursor));  // 需要用 QCursor 包装
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}

void UIButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit clicked();
    QGraphicsPixmapItem::mousePressEvent(event);
}