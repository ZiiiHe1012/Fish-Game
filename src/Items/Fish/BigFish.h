#ifndef BIGFISH_H
#define BIGFISH_H

#include "Fish.h"

class BigFish : public Fish {
public:
    explicit BigFish(QGraphicsItem *parent = nullptr);
    
    void updateMovement(qint64 deltaTime);
    
private:
    QPointF velocity;
    qint64 changeDirectionTimer{0};
};

#endif