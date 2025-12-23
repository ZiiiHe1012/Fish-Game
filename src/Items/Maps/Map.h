#ifndef MAP_H
#define MAP_H

#include <QGraphicsScene>
#include <QPointF>
#include "../Item.h"

class Map : public Item {
public:
    explicit Map(QGraphicsItem *parent = nullptr, const QString &pixmapPath = "");

    void scaleToFitScene(QGraphicsScene *scene);

    virtual qreal getFloorHeight(); // Need to rewrite to support multiple platforms

    virtual QPointF getSpawnPos();
};


#endif
