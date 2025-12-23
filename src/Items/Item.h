#ifndef ITEM_H
#define ITEM_H

#include <QGraphicsItem>
#include <QPainter>

class Item : public QGraphicsItem {
public:
    explicit Item(QGraphicsItem *parent, const QString &pixmapPath);

    [[nodiscard]] QRectF boundingRect() const override {
        if (pixmapItem != nullptr) {
            return this->pixmapItem->boundingRect();
        }
        return {};
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override {
    }
    
    QGraphicsPixmapItem* getPixmapItem() const { return pixmapItem; }

protected:
    QGraphicsPixmapItem *pixmapItem{};
};

#endif