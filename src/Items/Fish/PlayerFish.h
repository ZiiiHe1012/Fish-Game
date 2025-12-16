#ifndef PLAYERFISH_H
#define PLAYERFISH_H

#include "Fish.h"

class PlayerFish : public Fish {
public:
    explicit PlayerFish(QGraphicsItem *parent = nullptr);
    
    void setFacingLeft();
    void setFacingRight();

    QRectF boundingRect() const override;
};

#endif