#ifndef GOLDENFISH_H
#define GOLDENFISH_H

#include "Fish.h"

class GoldenFish : public Fish {
public:
    explicit GoldenFish(QGraphicsItem *parent = nullptr, bool moveRight = true);
    
    void updateMovement(qint64 deltaTime);
    
    QRectF boundingRect() const override;
    
private:
    QPointF velocity;
    bool facingLeft{false};
};

#endif