#ifndef MEDIUMFISH_H
#define MEDIUMFISH_H

#include "Fish.h"

class MediumFish : public Fish {
public:
    explicit MediumFish(QGraphicsItem *parent = nullptr, bool moveRight = true);
    
    void updateMovement(qint64 deltaTime);
    
    QRectF boundingRect() const override;
    
private:
    QPointF velocity;
    bool facingLeft{false};
};

#endif