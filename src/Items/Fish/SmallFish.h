#ifndef SMALLFISH_H
#define SMALLFISH_H

#include "Fish.h"

class SmallFish : public Fish {
public:
    explicit SmallFish(QGraphicsItem *parent = nullptr);
    
    void updateMovement(qint64 deltaTime);
    
private:
    QPointF velocity;
    qint64 changeDirectionTimer{0};
};

#endif