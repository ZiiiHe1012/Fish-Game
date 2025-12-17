#ifndef BATTLEFIELDLEVEL2_H
#define BATTLEFIELDLEVEL2_H

#include "Map.h"

class BattlefieldLevel2: public Map {
public:
    explicit BattlefieldLevel2(QGraphicsItem *parent= nullptr);

    qreal getFloorHeight() override;
};

#endif